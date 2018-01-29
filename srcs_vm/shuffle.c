/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shuffle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 23:07:51 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 00:06:01 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	shuffle_players(t_master *m)
{
	t_player	array[MAX_PLAYERS];
	int			i;

	ft_bzero(array, sizeof(t_player) * MAX_PLAYERS);
	i = -1;
	while (++i < m->player_count)
	{
		if (m->player[i].n_flag_pos != 0)
		{
			if (m->player[i].n_flag_pos < m->player_count)
				ft_memcpy(&array[empty_pos(array,
					m->player[i].n_flag_pos - 1, m)],
					m->player + i, sizeof(t_player));
			else
				m->player[i].n_flag_pos = 0;
		}
	}
	shuffle_players_part_two(array, m);
}

void	shuffle_players_part_two(t_player array[], t_master *m)
{
	int	i;

	i = -1;
	while (++i < m->player_count)
	{
		if (m->player[i].n_flag_pos == 0)
			ft_memcpy(&array[empty_pos(array, 0, m)], m->player + i,
				sizeof(t_player));
	}
	ft_memcpy(m->player, array, sizeof(t_player) * MAX_PLAYERS);
	i = -1;
	while (++i < m->player_count)
		m->player[i].id = P1_ID - i;
}

int		empty_pos(t_player array[], int i, t_master *m)
{
	if (i < m->player_count && array[i].id == 0)
		return (i);
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (array[i].id == 0)
			return (i);
	}
	return (-42);
}
