/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 00:45:02 by ashih             #+#    #+#             */
/*   Updated: 2018/01/26 23:48:17 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	put_hex(unsigned char c, WINDOW *win)
{
	static const char hextable[16] = "0123456789abcdef";

	waddch(win, hextable[c / 16]);
	waddch(win, hextable[c % 16]);
}

void	display_process_pc(t_master *m)
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
			wmove(m->win_core, 1 + (process->pc / 64),
				2 + (process->pc % 64) * 3);
			wattron(m->win_core, COLOR_PAIR(i + 1 + 4));
			put_hex(m->core[process->pc].value, m->win_core);
			wattroff(m->win_core, COLOR_PAIR(i + 1 + 4));
			process_list = process_list->next;
		}
	}
}

void	display_core(t_master *m)
{
	int		i;

	wmove(m->win_core, 0, 0);
	wprintw(m->win_core, "\n  ");
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (m->core[i].owner != 0)
		{
			wattron(m->win_core, COLOR_PAIR(m->core[i].owner));
			put_hex(m->core[i].value, m->win_core);
			wattroff(m->win_core, COLOR_PAIR(m->core[i].owner));
		}
		else
			put_hex(m->core[i].value, m->win_core);
		wprintw(m->win_core, i % 64 == 63 ? "\n  " : " ");
	}
	display_process_pc(m);
	find_lives(m);
	box(m->win_core, 0, 0);
	wrefresh(m->win_core);
}

void		find_lives(t_master *m)
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

			if (m->core[process->pc].value == 1)
				highlight_pid(process, m);

			process_list = process_list->next;
		}
	}
}

int			whose_pid(t_process *process, t_master *m)
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


void		highlight_pid(t_process *process, t_master *m)
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



void	display_control(t_master *m)
{
	wmove(m->win_control, 0, 0);
	wprintw(m->win_control, "\n\n  *PAUSE*\n");

	wprintw(m->win_control, "  Frame Skip:\t\t%d\n\n", m->frame_skip);

	wprintw(m->win_control, "  Cycles:\t\t%d\n\n", m->current_cycle);
	wprintw(m->win_control, "  CYCLE_TO_DIE:\t\t%d/%d\n",
			m->ctd_counter, m->cycle_to_die);
	wprintw(m->win_control, "  CYCLE_DELTA:\t\t%d\n", CYCLE_DELTA);
	wprintw(m->win_control, "  NBR_LIVE:\t\t%d/%d\n", total_lives(m), NBR_LIVE);
	wprintw(m->win_control, "  MAX_CHECKS:\t\t%d/%d\n", m->checks, MAX_CHECKS);
	wprintw(m->win_control, "\n  Current Lives Ratio:\n");
	wprintw(m->win_control, "  [----------------------------------------]\n");
	wprintw(m->win_control, "\n  Last Lives Ratio:\n");
	wprintw(m->win_control, "  [----------------------------------------]\n");
	wprintw(m->win_control, "\n  WINNER:\t\t%s\n", "????");
	box(m->win_control, 0, 0);
	wrefresh(m->win_control);
}

void	display_players(t_master *m)
{
	int	i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		display_player(i, m);
		box(m->win_player[i], 0, 0);
		wrefresh(m->win_player[i]);
	}
}

void	display_player(int i, t_master *m)
{
	wmove(m->win_player[i], 0, 0);
	if (i >= m->player_count)
	{
		wprintw(m->win_player[i], "\n  PLAYER %d:\t%s\n", i + 1, "N/A");
		return ;
	}
	wprintw(m->win_player[i], "\n  PLAYER %d:\t", i + 1);
	wattron(m->win_player[i], COLOR_PAIR(i + 1));
	wprintw(m->win_player[i], "%.33s\n", m->player[i].name);
	wattroff(m->win_player[i], COLOR_PAIR(i + 1));
	wprintw(m->win_player[i], "  COMMENT:\t%.33s\n", m->player[i].comment);
	wprintw(m->win_player[i], "\n  PLAYER ID:\t%X\n", m->player[i].id);
	wprintw(m->win_player[i], "\n  PROCESSES:\t%d\n",
			m->player[i].process_count);
	wprintw(m->win_player[i], "\n  LIVES:\t%d\n", m->player[i].lives);
	wprintw(m->win_player[i], "  LAST LIVES:\t%d\n", m->player[i].last_lives);
//	wprintw(m->win_player[i], "\n  AFF:\t\t%.33s\n", m->player[i].afflog);
	wprintw(m->win_player[i], "\n  AFF:");
	wattron(m->win_player[i], COLOR_PAIR(i + 1));
	wprintw(m->win_player[i], "\n  %.45s", m->player[i].afflog);
	wprintw(m->win_player[i], "\n  %.45s", m->player[i].afflog + 45);
	wprintw(m->win_player[i], "\n  %.45s", m->player[i].afflog + 45 * 2);
	wattroff(m->win_player[i], COLOR_PAIR(i + 1));
}
