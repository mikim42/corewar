/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 21:00:51 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 16:41:50 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int		ft_rand(void)
{
	static int		fd;
	unsigned int	result;

	if (fd <= 0)
		fd = open("/dev/urandom", O_RDONLY, 0);
	if (fd < 0)
		return (-1);
	read(fd, &result, sizeof(unsigned int));
	return (result);
}

void		verbose_intro(t_master *m)
{
	static const char *colours[MAX_PLAYERS] = {
		"{green}", "{yellow}", "{magenta}", "{cyan}" };
	int		i;

	ft_printf("Ladies and gentlemen, welcome to the"
		" COREWAAAAAAAAAAAAAAAAAAAAAR CHAMPIONSHIP GRAND PRIX "
		"%b!!!!!!!!!\n", ft_rand());
	ft_printf("Introducing our contestants...\n");
	i = -1;
	while (++i < m->player_count)
	{
		ft_printf("Player %d, weighing at %u bytes, ", i + 1,
			m->player[i].prog_size);
		ft_printf(colours[i]);
		ft_printf("{bold}%s{reset}!\n", m->player[i].name);
		ft_printf("  \"");
		ft_printf(colours[i]);
		ft_printf("%s{reset}\"\n", m->player[i].comment);
	}
}

void		verbose_outro(t_master *m)
{
	static const char *colours[MAX_PLAYERS] = {
		"{green}", "{yellow}", "{magenta}", "{cyan}" };

	ft_printf("\nThe winner is...\n");
	ft_printf(colours[-(m->winner->id) - 1]);
	ft_printf("  {bold}%s{reset}!!!!!!!!\n", m->winner->name);
}


int			main(int argc, char **argv)
{
	t_master	m;

	ft_bzero(&m, sizeof(t_master));
	m.d_flag = UNSET_VALUE;
	m.cycle_to_die = CYCLE_TO_DIE;
	m.ctd_counter = 0;
	if (parse_args(argc, argv, &m))
		return (0);
	if (m.v_flag)
	{
		init_ncurses_stuffz(&m);
		init_rainbow_road(&m);
	}
	else
	{
		verbose_intro(&m);
		while (!m.show_winner)
			step_forward(&m);
		verbose_outro(&m);
	}
	return (0);
}

void		build_last_cycle(t_master *m)
{
	m->current_cycle++;
	run_processes(m);
	reap_processes(m);
	ft_lstdel(&(m->process_list), del_process);
	if (m->winner == 0)
		m->winner = &(m->player[m->player_count - 1]);
}

void		step_forward(t_master *m)
{
	if (m->show_winner)
		return ;
	m->current_cycle++;
	run_processes(m);
	if (++(m->ctd_counter) >= m->cycle_to_die)
	{
		if (++(m->checks) >= MAX_CHECKS || m->nbr_lives >= NBR_LIVE)
		{
			m->cycle_to_die -= CYCLE_DELTA;
			m->checks = 0;
		}
		m->nbr_lives = 0;
		m->ctd_counter = 0;
		reap_processes(m);
		if (m->stop_at_death)
		{
			m->stop_at_death = 0;
			m->forward = 0;
		}
	}
	if (m->cycle_to_die <= 0 || m->process_list == 0)
		m->show_winner = 1;
	if (m->forward && !(m->show_winner) &&
			++(m->fs_counter) < m->frame_skip)
		return ;
	if (m->show_winner)
		build_last_cycle(m);
	m->fs_counter = 0;
	if (m->v_flag)
	{
		update_windows(m);
		update_rainbow_road(m);
	}
}

void		run_processes(t_master *m)
{
	t_list		*process_list;
	t_process	*process;

	process_list = m->process_list;
	while (process_list != 0)
	{
		process = process_list->content;
		run_process(process, m);
		process_list = process_list->next;
	}
}

void		run_process(t_process *process, t_master *m)
{
	if (process->cycles == 0)
		process->opcode = m->core[process->pc].value;

	if (!(1 <= process->opcode && process->opcode <= 16))
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
		return ;
	}
	if (++(process->cycles) >= (int)g_op_tab[process->opcode - 1].cycles)
	{
		g_op_tab[process->opcode - 1].func(process, m);
		process->cycles = 0;
	}
}
