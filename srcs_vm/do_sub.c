/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 03:07:34 by ashih             #+#    #+#             */
/*   Updated: 2018/01/27 03:07:46 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		do_sub(t_process *process, t_master *m)
{
	unsigned char	reg_num;

	if (validate_args(process))
	{
		reg_num = read_reg_exact(process, m, 2);
		process->reg[reg_num] =
			read_arg(process, m, 0) - read_arg(process, m, 1);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process)) % MEM_SIZE;
}
