/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:26:14 by ashih             #+#    #+#             */
/*   Updated: 2018/01/25 00:23:49 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			init_sprite_table(t_master *m)
{
	if (load_sprite(m->sprite_table + 0, SPRITE_00) ||
		load_sprite(m->sprite_table + 1, SPRITE_01) ||
		load_sprite(m->sprite_table + 2, SPRITE_02) ||
		load_sprite(m->sprite_table + 3, SPRITE_03))
		return (1);
	return (0);
}

int			load_sprite(t_sprite **sprite, char *file)
{
	int		fd;

	*sprite = ft_memalloc(sizeof(t_sprite));
	if ((fd = open(file, O_RDONLY)) == -1)
		return (ft_puterror(ERROR_SPRITE, 1));
	if (init_sprite_dimen(*sprite, fd))
		return (1);
	read_sprite_data(*sprite, fd);
	if (close(fd) == -1)
		return (ft_puterror(ERROR_CLOSE_FILE, 1));
	return (0);
}

int			init_sprite_dimen(t_sprite *sprite, int fd)
{
	char	*line;

	skip_next_line(fd, 1);
	get_next_line(fd, &line);
	sprite->width = ft_atoi(line + 1);
	sprite->height = ft_atoi(ft_strchr(line, ',') + 1);
	ft_strdel(&line);
	sprite->color = ft_memalloc(sizeof(int) * sprite->width * sprite->height);
	sprite->alpha = ft_memalloc(sizeof(int) * sprite->width * sprite->height);
	if (!(sprite->color && sprite->alpha))
		return (ft_puterror(ERROR_MEMORY, 1));
	return (0);
}

void		read_sprite_data(t_sprite *sprite, int fd)
{
	char	*line;
	int		r;
	int		g;
	int		b;
	int		i;

	i = 0;
	while (i < sprite->width * sprite->height)
	{
		get_next_line(fd, &line);
		r = ft_atoi(line);
		g = ft_atoi(ft_strchr(line, ' '));
		b = ft_atoi(ft_strchr(ft_strchr(line, ' ') + 1, ' '));
		sprite->alpha[i] = ft_atoi(ft_strchr(ft_strchr(ft_strchr(line, ' ') + 1,
			' ') + 1, ' '));
		sprite->color[i++] = (r << 16) + (g << 8) + b;
		ft_strdel(&line);
	}
}

void		draw_sprite(t_sprite *sprite, int x, int y, t_master *m)
{
	int		i;

	i = 0;
	while (i < sprite->width * sprite->height)
	{
		if (sprite->alpha[i] > 10)
			draw_dot(x + i % sprite->width, y + i / sprite->width,
				sprite->color[i], m);
		i++;
	}
}
