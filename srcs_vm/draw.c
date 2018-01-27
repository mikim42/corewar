/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:51:50 by ashih             #+#    #+#             */
/*   Updated: 2018/01/27 01:45:38 by ashih            ###   ########.fr       */
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

void	draw_process_pc(t_master *m)
{
	t_list		*process_list;
	t_process	*process;

	process_list = m->process_list;
	while (process_list != 0)
	{
		process = process_list->content;
		draw_sprite(m->sprite_table[-(process->player->id) - 1],
			m->core[process->pc].x - 7, m->core[process->pc].y - 7, m);
		process_list = process_list->next;
	}
}
