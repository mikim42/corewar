/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:26:14 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 15:28:02 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			init_sprite_x_table(t_master *m)
{
	int		i;
	int		red;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (load_sprite(m->sprite_x_table + i, SPRITE_X))
			return (1);
	i = -1;
	while (++i < m->sprite_x_table[0]->width * m->sprite_x_table[0]->height)
	{
		red = (m->sprite_x_table[0]->color[i].rgb & 0xFF0000) >> 16;
		m->sprite_x_table[0]->color[i].rgb = (red << 8);
		m->sprite_x_table[1]->color[i].rgb = (red << 16) | (red << 8);
		m->sprite_x_table[2]->color[i].rgb = (red << 16) | (red << 0);
		m->sprite_x_table[3]->color[i].rgb = (red << 8) | (red << 0);
	}
	return (0);
}

int			init_sprite_table(t_master *m)
{
	if (load_sprite(m->sprite_table + 0, SPRITE_00) ||
		load_sprite(m->sprite_table + 1, SPRITE_01) ||
		load_sprite(m->sprite_table + 2, SPRITE_02) ||
		load_sprite(m->sprite_table + 3, SPRITE_03) ||
		load_sprite(m->sprite_large_table + 0, SPRITE_LARGE_00) ||
		load_sprite(m->sprite_large_table + 1, SPRITE_LARGE_01) ||
		load_sprite(m->sprite_large_table + 2, SPRITE_LARGE_02) ||
		load_sprite(m->sprite_large_table + 3, SPRITE_LARGE_03))
		return (1);
	return (0);
}

int			load_sprite(t_sprite **sprite, char *file)
{
	int		fd;
	int		width;
	int		height;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ft_puterror(ERROR_SPRITE, 1));
	read(fd, &width, 4);
	read(fd, &height, 4);
	*sprite = ft_memalloc(sizeof(t_sprite) + sizeof(t_color) * width * height);
	if (*sprite == 0)
		return (ft_puterror(ERROR_MEMORY, 1));
	(*sprite)->width = width;
	(*sprite)->height = height;
	read(fd, (*sprite)->color, sizeof(t_color) * width * height);
	if (close(fd) == -1)
		return (ft_puterror(ERROR_CLOSE_FILE, 1));
	return (0);
}

void		draw_sprite(t_sprite *sprite, int x, int y, t_master *m)
{
	int		i;

	i = 0;
	while (i < sprite->width * sprite->height)
	{
		if (sprite->color[i].alpha > 10)
			draw_dot(x + i % sprite->width, y + i / sprite->width,
				sprite->color[i].rgb, m);
		i++;
	}
}
