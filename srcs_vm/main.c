/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 21:00:51 by ashih             #+#    #+#             */
/*   Updated: 2018/01/28 01:20:40 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			main(int argc, char **argv)
{
	t_master	m;

	ft_bzero(&m, sizeof(t_master));
	m.cycle_to_die = CYCLE_TO_DIE;
	m.ctd_counter = 0;
	if (argc == 1 || argc > 5)
		return (ft_puterror(ERROR_USAGE, 0));
	if (read_players(argc, argv, &m))
		return (1);
	init_ncurses_stuffz(&m);
	init_rainbow_road(&m);
	return (0);
}

int			process_should_die(void *process, size_t size)
{
	int		should_die;

	(void)size;
	should_die = ((t_process *)process)->lives == 0;
	((t_process *)process)->lives = 0;
	return (should_die);
}

void		del_process(void *process, size_t size)
{
	(void)size;
	((t_process *)process)->player->process_count--;
	ft_memdel(&process);
}


void		reap_processes(t_master *m)
{
	int			i;

	ft_lst_cond_remove(&(m->process_list), process_should_die,
		del_process);
	i = -1;
	while (++i < m->player_count)
	{
		m->player[i].last_lives = m->player[i].lives;
		m->player[i].lives = 0;
	}
}

void		build_last_cycle(t_master *m)
{
	m->current_cycle++;
	run_processes(m);
	reap_processes(m);
	ft_lstdel(&(m->process_list), del_process);
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
	}
	if (m->cycle_to_die <= 0 || m->process_list == 0)
		m->show_winner = 1;
	if (m->forward && !(m->show_winner) &&
			++(m->fs_counter) < m->frame_skip)
		return ;
	if (m->show_winner)
		build_last_cycle(m);
	m->fs_counter = 0;
	update_windows(m);
	update_rainbow_road(m);
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
