/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 18:42:45 by mikim             #+#    #+#             */
/*   Updated: 2018/01/27 02:47:01 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		validate_args(t_process *process, t_master *m)
{
	unsigned char	index;
	unsigned char	type;
	unsigned int	pos;
	unsigned int	i;

	index = process->opcode - 1;
	pos = 2;
	i = 0;
	while (i < g_op_tab[index].num_args)
	{
		type = get_type(process, m, i);
		if ((type == REG_CODE && !(g_op_tab[index].arg_types[i] & T_REG)) ||
			(type == DIR_CODE && !(g_op_tab[index].arg_types[i] & T_DIR)) ||
			(type == IND_CODE && !(g_op_tab[index].arg_types[i] & T_IND)) ||
			!type)
			return (0);
		if (type == REG_CODE &&
			!is_valid_reg(m->core[(process->pc + pos) % MEM_SIZE].value - 1))
			return (0);
		pos += count_bytes(type, g_op_tab[index].short_dir);
		i++;
	}
	return (1);
}

size_t	instruction_length(t_process *process, t_master *m)
{
	unsigned char	index;
	unsigned char	type;
	unsigned int	i;
	size_t			length;

	index = process->opcode - 1;
	length = 2;
	i = 0;
	while (i < g_op_tab[index].num_args)
	{
		type = get_type(process, m, i++);
		length += count_bytes(type, g_op_tab[index].short_dir);
	}
	return (length);
}

void	do_live(t_process *process, t_master *m)
{
	unsigned int	pid;
	int				i;

	process->lives++;
	pid = read_int(m, process->pc + 1);
	i = -1;
	while (++i < m->player_count)
	{
		if (pid == m->player[i].id)
		{
			m->player[i].lives++;
			m->winner = &(m->player[i]);
		}
	}
	process->pc = (process->pc + 5) % MEM_SIZE;
}

void	do_ld(t_process *process, t_master *m)
{
	unsigned char	reg_num;

	if (validate_args(process, m))
	{
		reg_num = read_reg_exact(process, m, 1);
		process->reg[reg_num] = read_arg(process, m, 0);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}

void	do_st(t_process *process, t_master *m)
{
	unsigned char	type;
	unsigned int	offset;

	if (validate_args(process, m))
	{
		type = m->core[(process->pc + 1) % MEM_SIZE].value;
		type = (type >> 4) & 3;
		if (type == T_REG)
		{
			process->reg[read_reg_exact(process, m, 1)] =
													read_arg(process, m, 0);
		}
		else
		{
			offset = process->pc;
			offset += read_ind_exact(process, m, 1) % IDX_MOD;
			write_int(process, m, offset, read_arg(process, m, 0));
		}
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}
