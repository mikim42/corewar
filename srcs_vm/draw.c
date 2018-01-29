/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:51:50 by ashih             #+#    #+#             */
/*   Updated: 2018/01/28 18:18:50 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	draw_dot(int x, int y, int color, t_master *m)
{
	if (0 <= x && x < WIN_WIDTH && 0 <= y && y < WIN_HEIGHT)
	{
		*(int *)(m->frame + (x + y * WIN_WIDTH) * m->bpp) = color;
	}
}

void	draw_square(int x, int y, int color, t_master *m)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SQ_SIZE)
	{
		j = -1;
		while (++j < SQ_SIZE)
			draw_dot(x + j, y + i, color, m);
	}
}

void	draw_big_square(int x, int y, int color, t_master *m)
{
	int	i;
	int	j;

	i = -1;
	while (++i < BIG_SQ_SIZE)
	{
		j = -1;
		while (++j < BIG_SQ_SIZE)
			draw_dot(x + j, y + i, color, m);
	}
	i = -1;
	while (++i < BIG_SQ_SIZE)
	{
		draw_dot(x + i, y, DEF_COLOR, m);
		draw_dot(x + i, y + BIG_SQ_SIZE, DEF_COLOR, m);
		draw_dot(x, y + i, DEF_COLOR, m);
		draw_dot(x + BIG_SQ_SIZE, y + i, DEF_COLOR, m);
	}
}

void	draw_process_pc(t_master *m)
{
	static const int	color_table[5] = {
		DEF_COLOR, P1_COLOR, P2_COLOR, P3_COLOR, P4_COLOR};
	t_list		*process_list;
	t_process	*process;

	process_list = m->process_list;
	while (process_list != 0)
	{
		process = process_list->content;
		if (m->e_flag)
			draw_sprite(m->sprite_table[-(process->player->id) - 1],
				m->core[process->pc].x - 7, m->core[process->pc].y - 7, m);
		else
			draw_big_square(m->core[process->pc].x - 2,
				m->core[process->pc].y - 2,
				color_table[-(process->player->id)], m);
		process_list = process_list->next;
	}
}
