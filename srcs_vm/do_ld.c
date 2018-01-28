/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 03:04:11 by ashih             #+#    #+#             */
/*   Updated: 2018/01/27 03:04:27 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	do_ld(t_process *process, t_master *m)
{
	unsigned char	reg_num;

	if (validate_args(process))
	{
		reg_num = read_reg_exact(process, m, 1);
		process->reg[reg_num] = read_arg(process, m, 0);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process)) % MEM_SIZE;
}
