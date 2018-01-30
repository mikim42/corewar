/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 21:49:59 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 23:14:26 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		free_all(t_master *m)
{
	int		i;

	free_ncurses_stuff(m);
	free_mlx_stuff(m);
	i = -1;
	while (++i < m->player_count)
		ft_memdel((void **)&(m->player[i].prog));
}

void		free_ncurses_stuff(t_master *m)
{
	int		i;

	safe_delwin(m->win_banner);
	safe_delwin(m->win_core);
	safe_delwin(m->win_control);
	safe_delwin(m->win_extra);
	i = -1;
	while (++i < MAX_PLAYERS)
		safe_delwin(m->win_player[i]);
}

void		safe_delwin(WINDOW *win)
{
	if (win)
		delwin(win);
}

void		free_mlx_stuff(t_master *m)
{
	int		i;

	if (m->win)
		mlx_destroy_window(m->mlx, m->win);
	if (m->img)
		mlx_destroy_image(m->mlx, m->img);
	if (m->mlx)
	{
		ft_memdel((void **)&(m->mlx->font[1]));
		ft_memdel((void **)&(m->mlx->font));
		ft_memdel((void **)&(m->mlx));
	}
	i = -1;
	while (++ i < MAX_PLAYERS * 3)
		ft_memdel((void **)&(m->sprite_table[i]));
}
