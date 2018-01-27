/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_four.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 18:47:38 by mikim             #+#    #+#             */
/*   Updated: 2018/01/26 19:39:52 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		do_add(t_process *process, t_master *m)
{
	unsigned char	reg_num;

	if (validate_args(process, m))
	{
		reg_num = read_reg_exact(process, m, 2);
		process->reg[reg_num] =
			read_arg(process, m, 0) + read_arg(process, m, 1);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}

void		do_sub(t_process *process, t_master *m)
{
	unsigned char	reg_num;

	if (validate_args(process, m))
	{
		reg_num = read_reg_exact(process, m, 2);
		process->reg[reg_num] =
			read_arg(process, m, 0) - read_arg(process, m, 1);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}

void		do_and(t_process *process, t_master *m)
{
	unsigned char	reg_num;

	if (validate_args(process, m))
	{
		reg_num = read_reg_exact(process, m, 2);
		process->reg[reg_num] =
			read_arg(process, m, 0) & read_arg(process, m, 1);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}

void		do_or(t_process *process, t_master *m)
{
	unsigned char	reg_num;

	if (validate_args(process, m))
	{
		reg_num = read_reg_exact(process, m, 2);
		process->reg[reg_num] =
			read_arg(process, m, 0) | read_arg(process, m, 1);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}

void		do_xor(t_process *process, t_master *m)
{
	unsigned char	reg_num;

	if (validate_args(process, m))
	{
		reg_num = read_reg_exact(process, m, 2);
		process->reg[reg_num] =
			read_arg(process, m, 0) ^ read_arg(process, m, 1);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}
