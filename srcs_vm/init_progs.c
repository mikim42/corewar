/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_progs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 00:31:43 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 00:31:46 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_progs(t_master *m)
{
	int	i;

	i = -1;
	while (++i < m->player_count)
		init_prog(i, m);
}

void	init_prog(int i, t_master *m)
{
	t_process		*first;
	unsigned int	j;

	first = ft_memalloc(sizeof(t_process));
	m->player[i].process_count++;
	first->player = &(m->player[i]);
	first->reg[0] = m->player[i].id;
	ft_lstadd(&(m->process_list),
		ft_lst_new_ref(first, sizeof(t_process)));
	first->pc = MEM_SIZE / (unsigned int)m->player_count * i;
	j = 0;
	while (j < m->player[i].prog_size)
	{
		m->core[(first->pc + j) % MEM_SIZE].value = m->player[i].prog[j];
		m->core[(first->pc + j) % MEM_SIZE].owner = i + 1;
		j++;
	}
}
