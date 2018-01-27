/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_five.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:40:44 by mikim             #+#    #+#             */
/*   Updated: 2018/01/26 19:40:50 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		do_zjmp(t_process *process, t_master *m)
{
	if (!(process->carry))
		process->pc = (process->pc + 3) % MEM_SIZE;
	else
	{
		process->pc += read_short(m, process->pc + 1) % IDX_MOD;
		process->pc %= MEM_SIZE;
	}
}

void		do_ldi(t_process *process, t_master *m)
{
	unsigned int	reg_num;
	unsigned int	offset;

	if (validate_args(process, m))
	{
		offset = process->pc;
		offset += (read_arg(process, m, 0) + read_arg(process, m, 1)) % IDX_MOD;
		reg_num = read_reg_exact(process, m, 2);
		process->reg[reg_num] = read_int(m, offset);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}

void		do_sti(t_process *process, t_master *m)
{
	unsigned int	offset;

	if (validate_args(process, m))
	{
		offset = process->pc;
		offset += (read_ind_exact(process, m, 1) + read_ind_exact(process, m, 2)) % IDX_MOD;
		write_int(process, m, offset, read_arg(process, m, 0));
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}

void		do_fork(t_process *process, t_master *m)
{
	t_process	new_process;

	ft_memcpy(&new_process, process, sizeof(t_process));
	new_process.pc += read_short(m, process->pc + 1) % IDX_MOD;
	new_process.pc %= MEM_SIZE;
	new_process.lives = 0;
	new_process.cycles = 0;
	new_process.opcode = 0;
	m->player[process->owner - 1].process_count++;
	ft_lstadd(&(m->player[process->owner - 1].process_list),
		ft_lstnew(&new_process, sizeof(t_process)));
	process->pc = (process->pc + 3) % MEM_SIZE;
}

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
