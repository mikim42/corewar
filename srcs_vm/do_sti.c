/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 03:10:25 by ashih             #+#    #+#             */
/*   Updated: 2018/01/27 03:10:35 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		do_sti(t_process *process, t_master *m)
{
	unsigned int	offset;

	if (validate_args(process, m))
	{
		offset = process->pc;
		offset += (read_arg(process, m, 1) +
					read_arg(process, m, 2)) % IDX_MOD;
		write_int(process, m, offset, read_arg(process, m, 0));
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}
