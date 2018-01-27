/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 03:03:43 by ashih             #+#    #+#             */
/*   Updated: 2018/01/27 03:04:02 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	do_live(t_process *process, t_master *m)
{
	unsigned int	pid;
	int				i;

	process->lives++;
	pid = read_int(m, process->pc + 1);
	i = -1;
	while (++i < m->player_count)
	{
		if (pid == m->player[i].id)
		{
			m->player[i].lives++;
			m->winner = &(m->player[i]);
		}
	}
	process->pc = (process->pc + 5) % MEM_SIZE;
}
