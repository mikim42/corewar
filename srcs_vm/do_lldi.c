/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 03:11:39 by ashih             #+#    #+#             */
/*   Updated: 2018/01/27 03:11:46 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		do_lldi(t_process *process, t_master *m)
{
	unsigned int	reg_num;
	unsigned int	offset;

	if (validate_args(process, m))
	{
		offset = process->pc;
		offset += read_larg(process, m, 0) + read_larg(process, m, 1);
		reg_num = read_reg_exact(process, m, 2);
		process->reg[reg_num] = read_int(m, offset);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}
