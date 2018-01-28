/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 03:10:54 by ashih             #+#    #+#             */
/*   Updated: 2018/01/27 03:11:02 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		do_lld(t_process *process, t_master *m)
{
	unsigned char	reg_num;

	if (validate_args(process, m))
	{
		reg_num = read_reg_exact(process, m, 1);
		process->reg[reg_num] = read_larg(process, m, 0);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}
