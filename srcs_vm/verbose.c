/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 19:55:13 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 19:57:32 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void					verbose_intro(t_master *m)
{
	static const char	*colours[MAX_PLAYERS] = {
		"{green}", "{yellow}", "{magenta}", "{cyan}" };
	int					i;

	ft_printf("Ladies and gentlemen, welcome to the"
		" COREWAAAAAAAAAAAAAAAAAAAAAR CHAMPIONSHIP GRAND PRIX "
		"%b!!!!!!!!!\n", ft_rand());
	ft_printf("Introducing our contestants...\n");
	i = -1;
	while (++i < m->player_count)
	{
		ft_printf("Player %d, weighing at %u bytes, ", i + 1,
			m->player[i].prog_size);
		ft_printf(colours[i]);
		ft_printf("{bold}%s{reset}!\n", m->player[i].name);
		ft_printf("  \"");
		ft_printf(colours[i]);
		ft_printf("%s{reset}\"\n", m->player[i].comment);
	}
}

void					verbose_outro(t_master *m)
{
	static const char *colours[MAX_PLAYERS] = {
		"{green}", "{yellow}", "{magenta}", "{cyan}" };

	ft_printf("\nThe winner is...\n");
	ft_printf(colours[-(m->winner->id) - 1]);
	ft_printf("  {bold}%s{reset}!!!!!!!!\n", m->winner->name);
}

void					dump_core(t_master *m)
{
	static const char	*colours[MAX_PLAYERS + 1] = {
		"", "{green}", "{yellow}", "{magenta}", "{cyan}" };
	int					i;

	ft_printf("\nCore Dump at Cycle %d\n", m->current_cycle);
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf(colours[m->core[i].owner]);
		ft_printf("%02x{reset}", m->core[i].value);
		ft_printf((i % 64 == 63) ? "\n" : " ");
	}
}
