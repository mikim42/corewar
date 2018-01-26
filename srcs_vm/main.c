/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 21:00:51 by ashih             #+#    #+#             */
/*   Updated: 2018/01/25 19:44:13 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			main(int argc, char **argv)
{
	t_master	m;
	ft_bzero(&m, sizeof(t_master));

	m.cycle_to_die = CYCLE_TO_DIE;
	m.cycle_delta = 0;
	m.nbr_live = NBR_LIVE;			// wtf is this?
	m.max_checks = MAX_CHECKS;		// and this?

	if (argc == 1 || argc > 5)
		return (ft_puterror(ERROR_USAGE, 0));
	if (read_players(argc, argv, &m))
		return (1);

	init_ncurses_stuffz(&m);
	init_rainbow_road(&m);

	// minilibx handles events and updates both minilibx and ncurses windows
	//
	// with minilibx window selected,
	//   tap RIGHT ARROW to go to next cycle
	//   hold UP ARROW to fast-forward to next cycles

	return (0);
}

void		step_forward(t_master *m)
{
	if (m->cycle_to_die < 0)
		return ;
	m->current_cycle++;
	m->cycle_delta++;
	if (m->cycle_delta == CYCLE_DELTA)
	{
		m->cycle_delta = 0;
		m->cycle_to_die -= CYCLE_DELTA;
	}
	run_processes(m);
	update_windows(m);
	update_rainbow_road(m);
}

void		run_processes(t_master *m)
{
	int			i;
	t_list		*process_list;
	t_process	*process;

	i = -1;
	while (++i < m->player_count)
	{
		process_list = m->player[i].process_list;
		while (process_list != 0)
		{
			process = process_list->content;

			run_process(process, m);

			process_list = process_list->next;
		}
	}
}

void		run_process(t_process *process, t_master *m)
{
	int		i;
	unsigned char last_opcode;

	i = -1;
	while (g_op_tab[++i].opcode != 0)
	{
		if (g_op_tab[i].opcode == (unsigned char)m->core[process->pc].value)
		{
			if (++process->cycles == (int)g_op_tab[i].cycles)
			{
				last_opcode = g_op_tab[i].opcode;
				g_op_tab[i].func(process, m);
				process->cycles = 0;
			}
			return ;
		}
	}
	// for invalid opcode, just move to next core position
	process->pc = (process->pc + 1) % MEM_SIZE;
}
