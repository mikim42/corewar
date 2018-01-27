/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_six.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:41:07 by mikim             #+#    #+#             */
/*   Updated: 2018/01/27 01:33:23 by ashih            ###   ########.fr       */
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
		offset += read_arg(process, m, 0) + read_arg(process, m, 1);
		reg_num = read_reg_exact(process, m, 2);
		process->reg[reg_num] = read_int(m, offset);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}

void		do_lfork(t_process *process, t_master *m)
{
	t_process	new_process;

	ft_memcpy(&new_process, process, sizeof(t_process));
	new_process.pc += read_short(m, process->pc + 1);
	new_process.pc %= MEM_SIZE;
	new_process.cycles = 0;
	new_process.opcode = 0;
	process->player->process_count++;
	ft_lstadd(&(m->process_list),
		ft_lstnew(&new_process, sizeof(t_process)));
	process->pc = (process->pc + 3) % MEM_SIZE;
}

void		append_afflog(unsigned int reg_num, t_process *process)
{
	char	*afflog;
	int		i;

	afflog = process->player->afflog;
	i = 0;
	while (afflog[i])
		i++;
	if (i != AFFLOG_SIZE)
	{
		afflog[i] = process->reg[reg_num] % 256;
		return ;
	}
	i = -1;
	while (++i < AFFLOG_SIZE - 1)
		afflog[i] = afflog[i + 1];
	afflog[i] = process->reg[reg_num] % 256;
}

void		do_aff(t_process *process, t_master *m)
{
	if (validate_args(process, m))
		append_afflog(read_reg_exact(process, m, 0), process);
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}
