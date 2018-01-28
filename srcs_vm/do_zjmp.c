/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 03:09:40 by ashih             #+#    #+#             */
/*   Updated: 2018/01/27 03:09:54 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		do_zjmp(t_process *process, t_master *m)
{
	(void)m;
	if (!(process->carry))
		process->pc = (process->pc + 3) % MEM_SIZE;
	else
	{
		process->pc += cached_short(process, 1) % IDX_MOD;
		process->pc %= MEM_SIZE;
	}
}
