/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_lives_bar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 00:22:35 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 00:24:03 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_lives_bar(t_master *m)
{
	int		i;
	int		j;
	int		filled_so_far;
	int		count;

	if (total_lives(m) == 0)
		return ;
	filled_so_far = 0;
	i = -1;
	while (++i < m->player_count - 1)
	{
		count = ft_round_dbl((double)m->player[i].lives / total_lives(m) *
			LIFEBAR_WIDTH);
		wattron(m->win_control, COLOR_PAIR(i + 5));
		j = -1;
		while (++j < count && filled_so_far < LIFEBAR_WIDTH)
			wprintw(m->win_control, " ") ? filled_so_far++ : filled_so_far++;
		wattroff(m->win_control, COLOR_PAIR(i + 5));
	}
	wattron(m->win_control, COLOR_PAIR(i + 5));
	count = LIFEBAR_WIDTH - filled_so_far;
	j = -1;
	while (++j < count)
		wprintw(m->win_control, " ");
	wattroff(m->win_control, COLOR_PAIR(i + 5));
}

int			total_lives(t_master *m)
{
	int		total;
	int		i;

	total = 0;
	i = -1;
	while (++i < m->player_count)
	{
		total += m->player[i].lives;
	}
	return (total);
}

void		display_last_lives_bar(t_master *m)
{
	int		i;
	int		j;
	int		filled_so_far;
	int		count;

	if (total_last_lives(m) == 0)
		return ;
	filled_so_far = 0;
	i = -1;
	while (++i < m->player_count - 1)
	{
		count = ft_round_dbl((double)m->player[i].last_lives /
			total_last_lives(m) * LIFEBAR_WIDTH);
		wattron(m->win_control, COLOR_PAIR(i + 5));
		j = -1;
		while (++j < count && filled_so_far < LIFEBAR_WIDTH)
			wprintw(m->win_control, " ") ? filled_so_far++ : filled_so_far++;
		wattroff(m->win_control, COLOR_PAIR(i + 5));
	}
	wattron(m->win_control, COLOR_PAIR(i + 5));
	count = LIFEBAR_WIDTH - filled_so_far;
	j = -1;
	while (++j < count)
		wprintw(m->win_control, " ");
	wattroff(m->win_control, COLOR_PAIR(i + 5));
}

int			total_last_lives(t_master *m)
{
	int		total;
	int		i;

	total = 0;
	i = -1;
	while (++i < m->player_count)
	{
		total += m->player[i].last_lives;
	}
	return (total);
}
