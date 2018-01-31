/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 17:44:02 by ashih             #+#    #+#             */
/*   Updated: 2018/01/30 17:44:24 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		step_forward(t_master *m)
{
	if (m->show_winner)
		return ;
	if (m->current_cycle == m->d_flag)
		dump_core(m);
	m->current_cycle++;
	run_processes(m);
	update_cycle_to_die(m);
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

void		update_cycle_to_die(t_master *m)
{
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
