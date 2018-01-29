/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_players.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 00:31:17 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 00:31:20 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	wprintw(m->win_player[i], "  PLAYER ID:\t%X\n", m->player[i].id);
	wprintw(m->win_player[i], "\n  PROCESSES:\t%d\n\n",
			m->player[i].process_count);
	wprintw(m->win_player[i], "  LAST LIVE:\t%d", m->player[i].cycle_last_live);
	wprintw(m->win_player[i], "\n  LIVES:\t%d\n", m->player[i].lives);
	wprintw(m->win_player[i], "  PREV LIVES:\t%d\n", m->player[i].last_lives);
	wprintw(m->win_player[i], "\n  AFF:");
	wattron(m->win_player[i], COLOR_PAIR(i + 1));
	wprintw(m->win_player[i], "\n  %.45s", m->player[i].afflog);
	wprintw(m->win_player[i], "\n  %.45s", m->player[i].afflog + 45);
	wprintw(m->win_player[i], "\n  %.45s", m->player[i].afflog + 45 * 2);
	wattroff(m->win_player[i], COLOR_PAIR(i + 1));
}
