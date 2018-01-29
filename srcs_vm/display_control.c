/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 00:24:48 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 00:34:19 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	display_control(t_master *m)
{
	wmove(m->win_control, 0, 0);
	wprintw(m->win_control, "\n  %s\n",
		(m->forward ? "*FAST FORWARD*" : "*PAUSE*"));
	wprintw(m->win_control, "  Frame Skip:\t\t%d\n", m->frame_skip);
	wprintw(m->win_control, "\n  Cycles:\t\t%d\n", m->current_cycle);
	wprintw(m->win_control, "\n  CYCLE_TO_DIE:\t\t%d/%d\n",
			m->ctd_counter, m->cycle_to_die);
	wprintw(m->win_control, "  CYCLE_DELTA:\t\t%d\n", CYCLE_DELTA);
	wprintw(m->win_control, "  NBR_LIVE:\t\t%d/%d\n", m->nbr_lives, NBR_LIVE);
	wprintw(m->win_control, "  MAX_CHECKS:\t\t%d/%d\n", m->checks, MAX_CHECKS);
	wprintw(m->win_control, "\n  Total Processes:\t%d\n", total_processes(m));
	wprintw(m->win_control, "\n  Current Lives Ratio:\n  ");
	display_lives_bar(m);
	wprintw(m->win_control, "\n\n  Last Lives Ratio:\n  ");
	display_last_lives_bar(m);
	display_winner(m);
	box(m->win_control, 0, 0);
	wrefresh(m->win_control);
}

int		total_processes(t_master *m)
{
	int	total;
	int	i;

	total = 0;
	i = -1;
	while (++i < m->player_count)
		total += m->player[i].process_count;
	return (total);
}

void	display_winner(t_master *m)
{
	if (m->show_winner == 0)
		return ;
	if (m->winner == 0)
		m->winner = &(m->player[m->player_count - 1]);
	wprintw(m->win_control, "\n\n  WINNER:\t\t");
	wattron(m->win_control, COLOR_PAIR(-(m->winner->id)));
	wprintw(m->win_control, "%.24s", m->winner->name);
	wattroff(m->win_control, COLOR_PAIR(-(m->winner->id)));
}
