/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 00:36:50 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 00:36:56 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

void	put_hex(unsigned char c, WINDOW *win)
{
	static const char hextable[16] = "0123456789abcdef";

	waddch(win, hextable[c / 16]);
	waddch(win, hextable[c % 16]);
}
