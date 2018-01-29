/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:53:27 by ashih             #+#    #+#             */
/*   Updated: 2018/01/28 19:50:30 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

short		read_short(t_master *m, unsigned int offset)
{
	return (((short)m->core[(offset + 0) % MEM_SIZE].value << 8) |
			((short)m->core[(offset + 1) % MEM_SIZE].value << 0));
}

int			read_int(t_master *m, unsigned int offset)
{
	return (((int)m->core[(offset + 0) % MEM_SIZE].value << 24) |
			((int)m->core[(offset + 1) % MEM_SIZE].value << 16) |
			((int)m->core[(offset + 2) % MEM_SIZE].value << 8) |
			((int)m->core[(offset + 3) % MEM_SIZE].value << 0));
}

void		write_int(t_process *process, t_master *m,
						unsigned int offset, int value)
{
	m->core[(offset + 0) % MEM_SIZE].value = (value >> 24) & 0xFF;
	m->core[(offset + 1) % MEM_SIZE].value = (value >> 16) & 0xFF;
	m->core[(offset + 2) % MEM_SIZE].value = (value >> 8) & 0xFF;
	m->core[(offset + 3) % MEM_SIZE].value = (value >> 0) & 0xFF;
	m->core[(offset + 0) % MEM_SIZE].owner = -(process->player->id);
	m->core[(offset + 1) % MEM_SIZE].owner = -(process->player->id);
	m->core[(offset + 2) % MEM_SIZE].owner = -(process->player->id);
	m->core[(offset + 3) % MEM_SIZE].owner = -(process->player->id);
}
