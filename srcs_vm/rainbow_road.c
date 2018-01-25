/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow_road.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 00:26:23 by ashih             #+#    #+#             */
/*   Updated: 2018/01/25 00:37:01 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			init_minilibx(t_master *m)
{
	if (!(m->mlx = mlx_init()) ||
		!(m->win = mlx_new_window(m->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME)) ||
		!(m->img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT)) ||
		!(m->frame = mlx_get_data_addr(m->img, &(m->bpp), &(m->size_line),
			&(m->endian))))
		return (ft_puterror(ERROR_MEMORY, 1));
	m->bpp /= 8;

	init_sprite_table(m);
	assign_core_pos(m);
	
	mlx_hook(m->win, 2, 0, key_press_hook, m);
	mlx_hook(m->win, 3, 0, key_release_hook, m);
	mlx_loop_hook(m->mlx, loop_hook, m);
	return (0);
}

void		assign_core_pos(t_master *m)
{
	static const int radius_table[16] = {WIN_WIDTH / 2 - 5, WIN_WIDTH / 2 - 10,
		WIN_WIDTH / 2 - 15, WIN_WIDTH / 2 - 20, WIN_WIDTH / 2 - 30,
		WIN_WIDTH / 2 - 35, WIN_WIDTH / 2 - 40, WIN_WIDTH / 2 - 45,
		WIN_WIDTH / 2 - 55, WIN_WIDTH / 2 - 60, WIN_WIDTH / 2 - 65,
		WIN_WIDTH / 2 - 70, WIN_WIDTH / 2 - 80, WIN_WIDTH / 2 - 85,
		WIN_WIDTH / 2 - 90, WIN_WIDTH / 2 - 95};
	int		radius;
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		radius = radius_table[15 - (i % 16)];
		m->core[i].x = WIN_WIDTH / 2 + ft_round_dbl((double)radius *
			-1.0 * cos(2.0 * M_PI * (double)(i / 16) / 256.0));
		m->core[i].y = WIN_HEIGHT / 2 + ft_round_dbl((double)radius *
			-1.0 * sin(2.0 * M_PI * (double)(i / 16) / 256.0));
	}
}

void		init_rainbow_road(t_master *m)
{
	static const int color_table[5] = {DEF_COLOR, P1_COLOR, P2_COLOR, P3_COLOR,
		P4_COLOR};
	int		i;

	init_minilibx(m);
	i = -1;
	while (++i < MEM_SIZE)
	{
		// draw core
		draw_square(m->core[i].x, m->core[i].y, color_table[m->core[i].owner],
			m);
	}
	// draw processes
	draw_process_pc(m);

	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	
	char	*str;
	str = ft_itoa(m->current_cycle);
	mlx_string_put(m->mlx, m->win, 0, 0, DEF_COLOR, "CYCLE: ");
	mlx_string_put(m->mlx, m->win, 80, 0, DEF_COLOR, str);
	ft_strdel(&str);


	mlx_loop(m->mlx);
}

void		update_rainbow_road(t_master *m)
{
	static const int color_table[5] = {DEF_COLOR, P1_COLOR, P2_COLOR, P3_COLOR,
		P4_COLOR};
	char	*str;
	int		i;

	mlx_clear_window(m->mlx, m->win);
	ft_bzero(m->frame, WIN_WIDTH * WIN_HEIGHT * m->bpp);

	i = -1;
	while (++i < MEM_SIZE)
	{
		// draw core
		draw_square(m->core[i].x, m->core[i].y, color_table[m->core[i].owner],
			m);
	}
	// draw processes
	draw_process_pc(m);

	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	
	str = ft_itoa(m->current_cycle);
	mlx_string_put(m->mlx, m->win, 0, 0, DEF_COLOR, "CYCLE: ");
	mlx_string_put(m->mlx, m->win, 80, 0, DEF_COLOR, str);
	ft_strdel(&str);
}
