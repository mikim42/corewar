/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 23:22:43 by ashih             #+#    #+#             */
/*   Updated: 2018/01/23 21:53:50 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_all_players(t_master *m)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (i < m->player_count)
			print_player(m->player + i);
		else
			ft_printf("PLAYER %d NOT FOUND LOL\n", i + 1);
	}
}

void		print_player(t_player *p)
{
	static const char hextable[] = "0123456789abcdef";

	ft_printf("player id = %d\n", p->id);
	ft_printf("name = %s\n", p->name);
	ft_printf("comment = %s\n", p->comment);
	ft_printf("prog_size = %u\n", p->prog_size);

	ft_printf("prog:\n");
	for (unsigned int i = 0; i < p->prog_size; i++)
	{
		ft_printf("%c%c ", hextable[p->prog[i] / 16], hextable[p->prog[i] % 16]);
		if (i % 16 == 15)
			ft_printf("\n");
	}
	ft_printf("\n\n");
}

void		print_core(t_master *m)
{
	int		i;

	ft_printf("PRINT_CORE()...\n");
	i = -1;
	while (++i < MEM_SIZE)
	{
		ft_printf("i=%d, core value = %#hhx, owner = %d\n",
			i, m->core[i].value, m->core[i].owner);
	}
	ft_printf("\n");
}
