/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_process_pc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 00:34:49 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 00:35:43 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				display_process_pc(t_master *m)
{
	t_list			*process_list;
	t_process		*process;

	process_list = m->process_list;
	while (process_list != 0)
	{
		process = process_list->content;
		wmove(m->win_core, 1 + (process->pc / 64),
			2 + (process->pc % 64) * 3);
		wattron(m->win_core, COLOR_PAIR(-(process->player->id) + 4));
		put_hex(m->core[process->pc].value, m->win_core);
		wattroff(m->win_core, COLOR_PAIR(-(process->player->id) + 4));
		process_list = process_list->next;
	}
}

void				find_lives(t_master *m)
{
	t_list			*process_list;
	t_process		*process;

	process_list = m->process_list;
	while (process_list != 0)
	{
		process = process_list->content;
		if (m->core[process->pc].value == 1)
			highlight_pid(process, m);
		process_list = process_list->next;
	}
}

void				highlight_pid(t_process *process, t_master *m)
{
	unsigned int	temp_pc;
	int				color;
	int				i;

	color = whose_pid(process, m);
	temp_pc = process->pc;
	wattron(m->win_core, WA_BOLD);
	wattron(m->win_core, COLOR_PAIR(color));
	i = -1;
	while (++i < 4)
	{
		temp_pc = (temp_pc + 1) % MEM_SIZE;
		wmove(m->win_core, 1 + (temp_pc / 64),
			2 + (temp_pc % 64) * 3);
		put_hex(m->core[temp_pc].value, m->win_core);
	}
	wattroff(m->win_core, COLOR_PAIR(color));
	wattroff(m->win_core, WA_BOLD);
}

int					whose_pid(t_process *process, t_master *m)
{
	unsigned int	pid;
	int				i;

	pid = (unsigned int)read_int(m, process->pc + 1);
	i = -1;
	while (++i < m->player_count)
	{
		if (pid == m->player[i].id)
			return (9 + i);
	}
	return (13);
}
