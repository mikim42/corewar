/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 21:00:51 by ashih             #+#    #+#             */
/*   Updated: 2018/02/03 17:20:30 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			main(int argc, char **argv)
{
	t_master	m;

	ft_bzero(&m, sizeof(t_master));
	m.d_flag = DUMMY_VALUE;
	m.cycle_to_die = CYCLE_TO_DIE;
	if (parse_args(argc, argv, &m))
		return (0);
	if (m.d_flag != DUMMY_VALUE)
		m.v_flag = 0;
	if (m.v_flag)
	{
		if (init_rainbow_road(&m) || init_ncurses_stuffz(&m))
			terminate(&m);
		mlx_loop(m.mlx);
	}
	else
	{
		verbose_intro(&m);
		while (!m.show_winner)
			step_forward(&m);
		verbose_outro(&m);
		free_all(&m);
	}
	return (0);
}
