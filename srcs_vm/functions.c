/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:53:27 by ashih             #+#    #+#             */
/*   Updated: 2018/01/26 00:39:26 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

size_t		count_bytes(unsigned char arg_code, int short_dir)
{
	if (arg_code == REG_CODE)
		return (1);
	else if (arg_code == IND_CODE)
		return (2);
	else if (arg_code == DIR_CODE && short_dir)
		return (2);
	else if (arg_code == DIR_CODE && !short_dir)
		return (4);
	return (0);
}

int			is_valid_reg(unsigned char reg_num)
{
	return (reg_num >= 0 && reg_num < REG_NUMBER);
}

short		read_short(t_master *m, unsigned int offset)
{
	return (((short)m->core[(offset + 0) % MEM_SIZE].value << 8) |
			((short)m->core[(offset + 1) % MEM_SIZE].value << 0));
}

int			read_int(t_master *m, unsigned int offset)
{
	return (((int)m->core[(offset + 0) % MEM_SIZE].value << 24) |
			((int)m->core[(offset + 1) % MEM_SIZE].value << 16) |
			((int)m->core[(offset + 2) % MEM_SIZE].value << 8) |
			((int)m->core[(offset + 3) % MEM_SIZE].value << 0));
}

void		write_int(t_process *process, t_master *m, unsigned int offset, int value)
{
	m->core[(offset + 0) % MEM_SIZE].value = (value >> 24) & 0xFF;
	m->core[(offset + 1) % MEM_SIZE].value = (value >> 16) & 0xFF;
	m->core[(offset + 2) % MEM_SIZE].value = (value >> 8) & 0xFF;
	m->core[(offset + 3) % MEM_SIZE].value = (value >> 0) & 0xFF;
	m->core[(offset + 0) % MEM_SIZE].owner = process->owner;
	m->core[(offset + 1) % MEM_SIZE].owner = process->owner;
	m->core[(offset + 2) % MEM_SIZE].owner = process->owner;
	m->core[(offset + 3) % MEM_SIZE].owner = process->owner;
}

int			read_arg_exact(t_process *process, t_master *m, unsigned int arg)
{
	unsigned char	opcode;
	unsigned char	type;
	unsigned int	pos;
	unsigned int	i;

	opcode = m->core[process->pc % MEM_SIZE].value;
	pos = 2;
	i = 0;
	while (i < arg)
	{
		type = m->core[(process->pc + 1) % MEM_SIZE].value;
		type = (type >> (2 * (3 - i++))) & 3;
		pos += count_bytes(type, g_op_tab[opcode - 1].short_dir);
	}
	type = m->core[(process->pc + 1) % MEM_SIZE].value;
	type = (type >> (2 * (3 - arg))) & 3;
	if (type == REG_CODE)
		return (m->core[(process->pc + pos) % MEM_SIZE].value - 1);
	else if (type == IND_CODE)
		return (read_short(m, process->pc + pos));
	else if (type == DIR_CODE && g_op_tab[opcode - 1].short_dir)
		return (read_short(m, process->pc + pos));
	else if (type == DIR_CODE)
		return (read_int(m, process->pc + pos));
	return (0);
}

int			read_reg_exact(t_process *process, t_master *m, unsigned int arg)
{
	unsigned char	opcode;
	unsigned char	type;
	unsigned int	pos;
	unsigned int	i;

	opcode = m->core[process->pc % MEM_SIZE].value;
	pos = 2;
	i = 0;
	while (i < arg)
	{
		type = m->core[(process->pc + 1) % MEM_SIZE].value;
		type = (type >> (2 * (3 - i++))) & 3;
		pos += count_bytes(type, g_op_tab[opcode - 1].short_dir);
	}
	type = m->core[(process->pc + 1) % MEM_SIZE].value;
	type = (type >> (2 * (3 - arg))) & 3;
	if (type == REG_CODE)
		return (m->core[(process->pc + pos) % MEM_SIZE].value - 1);
	else if (type == IND_CODE)
		return (read_int(m, ((int)process->pc +
				(read_short(m, process->pc + pos) % IDX_MOD))));
	else if (type == DIR_CODE && g_op_tab[opcode - 1].short_dir)
		return (read_short(m, process->pc + pos));
	else if (type == DIR_CODE)
		return (read_int(m, process->pc + pos));
	return (0);
}

int			read_ind_exact(t_process *process, t_master *m, unsigned int arg)
{
	unsigned char	opcode;
	unsigned char	type;
	unsigned int	p;
	unsigned int	i;

	opcode = m->core[process->pc % MEM_SIZE].value;
	p = 2;
	i = 0;
	while (i < arg)
	{
		type = m->core[(process->pc + 1) % MEM_SIZE].value;
		type = (type >> (2 * (3 - i++))) & 3;
		p += count_bytes(type, g_op_tab[opcode - 1].short_dir);
	}
	type = m->core[(process->pc + 1) % MEM_SIZE].value;
	type = (type >> (2 * (3 - arg))) & 3;
	if (type == REG_CODE)
		return (process->reg[m->core[(process->pc + p) % MEM_SIZE].value - 1]);
	else if (type == IND_CODE)
		return (read_short(m, process->pc + p));
	else if (type == DIR_CODE && g_op_tab[opcode - 1].short_dir)
		return (read_short(m, process->pc + p));
	else if (type == DIR_CODE)
		return (read_int(m, process->pc + p));
	return (0);
}

int			read_arg(t_process *process, t_master *m, unsigned int arg)
{
	unsigned char	opcode;
	unsigned char	type;
	unsigned int	p;
	unsigned int	i;

	opcode = m->core[process->pc % MEM_SIZE].value;
	p = 2;
	i = 0;
	while (i < arg)
	{
		type = m->core[(process->pc + 1) % MEM_SIZE].value;
		type = (type >> (2 * (3 - i++))) & 3;
		p += count_bytes(type, g_op_tab[opcode - 1].short_dir);
	}
	type = m->core[(process->pc + 1) % MEM_SIZE].value;
	type = (type >> (2 * (3 - arg))) & 3;
	if (type == REG_CODE)
		return (process->reg[m->core[(process->pc + p) % MEM_SIZE].value - 1]);
	else if (type == IND_CODE)
		return (read_int(m, ((int)process->pc +
				(read_short(m, process->pc + p) % IDX_MOD))));
	else if (type == DIR_CODE && g_op_tab[opcode - 1].short_dir)
		return (read_short(m, process->pc + p));
	else if (type == DIR_CODE)
		return (read_int(m, process->pc + p));
	return (0);
}

int			read_larg(t_process *process, t_master *m, unsigned int arg)
{
	unsigned char	opcode;
	unsigned char	type;
	unsigned int	p;
	unsigned int	i;

	opcode = m->core[process->pc % MEM_SIZE].value;
	p = 2;
	i = 0;
	while (i < arg)
	{
		type = m->core[(process->pc + 1) % MEM_SIZE].value;
		type = (type >> (2 * (3 - i++))) & 3;
		p += count_bytes(type, g_op_tab[opcode - 1].short_dir);
	}
	type = m->core[(process->pc + 1) % MEM_SIZE].value;
	type = (type >> (2 * (3 - arg))) & 3;
	if (type == REG_CODE)
		return (process->reg[m->core[(process->pc + p) % MEM_SIZE].value - 1]);
	else if (type == IND_CODE)
		return (read_int(m, ((int)process->pc +
				read_short(m, process->pc + p))));
	else if (type == DIR_CODE && g_op_tab[opcode - 1].short_dir)
		return (read_short(m, process->pc + p));
	else if (type == DIR_CODE)
		return (read_int(m, process->pc + p));
	return (0);
}

int			validate_args(t_process *process, t_master *m)
{
	unsigned char	index;
	unsigned char	type;
	unsigned int	pos;
	unsigned int	i;

	index = m->core[process->pc % MEM_SIZE].value - 1;
	pos = 2;
	i = 0;
	while (i < g_op_tab[index].num_args)
	{
		type = m->core[(process->pc + 1) % MEM_SIZE].value;
		type = (type >> (2 * (3 - i))) & 3;
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

size_t		instruction_length(t_process *process, t_master *m)
{
	unsigned char	index;
	unsigned char	type;
	unsigned int	i;
	size_t			length;

	index = m->core[process->pc % MEM_SIZE].value - 1;
	length = 2;
	i = 0;
	while (i < g_op_tab[index].num_args)
	{
		type = m->core[(process->pc + 1) % MEM_SIZE].value;
		type = (type >> (2 * (3 - i++))) & 3;
		length += count_bytes(type, g_op_tab[index].short_dir);
	}
	return (length);
}

void		do_live(t_process *process, t_master *m)
{
	unsigned int	arg1;

	process->lives++;
	arg1 = read_int(m, process->pc + 1);
	if (arg1 == m->player[0].id)
		m->player[0].lives++;
	else if (arg1 == m->player[1].id)
		m->player[1].lives++;
	else if (arg1 == m->player[2].id)
		m->player[2].lives++;
	else if (arg1 == m->player[3].id)
		m->player[3].lives++;
	process->pc = (process->pc + 5) % MEM_SIZE;
}

void		do_ld(t_process *process, t_master *m)
{
	unsigned char	reg_num;

	if (validate_args(process, m))
	{
		reg_num = m->core[(process->pc + 2) % MEM_SIZE].value - 1;
		process->reg[reg_num] = read_arg(process, m, 1);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}

void		do_st(t_process *process, t_master *m)
{
	unsigned char	reg_num;
	unsigned char	type;
	unsigned int	offset;

	if (validate_args(process, m))
	{
		type = m->core[(process->pc + 1) % MEM_SIZE].value;
		type = (type >> 4) & 3;
		reg_num = m->core[(process->pc + 2) % MEM_SIZE].value - 1;
		if (type == T_REG)
			process->reg[read_reg_exact(process, m, 1)] = process->reg[reg_num];
		else
		{
			offset = process->pc;
			offset += read_ind_exact(process, m, 1) % IDX_MOD;
			write_int(process, m, offset, process->reg[reg_num]);
		}
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}

void		do_add(t_process *process, t_master *m)
{
	unsigned char	reg_num;
	unsigned char	reg_num2;
	unsigned char	reg_num3;

	reg_num = m->core[(process->pc + 2) % MEM_SIZE].value - 1;
	reg_num2 = m->core[(process->pc + 3) % MEM_SIZE].value - 1;
	reg_num3 = m->core[(process->pc + 4) % MEM_SIZE].value - 1;
	if (is_valid_reg(reg_num) && is_valid_reg(reg_num2) &&
		is_valid_reg(reg_num3))
	{
		process->reg[reg_num3] = process->reg[reg_num] + process->reg[reg_num2];
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + 4) % MEM_SIZE;
}

void		do_sub(t_process *process, t_master *m)
{
	unsigned char	reg_num;
	unsigned char	reg_num2;
	unsigned char	reg_num3;

	reg_num = m->core[(process->pc + 2) % MEM_SIZE].value - 1;
	reg_num2 = m->core[(process->pc + 3) % MEM_SIZE].value - 1;
	reg_num3 = m->core[(process->pc + 4) % MEM_SIZE].value - 1;
	if (is_valid_reg(reg_num) && is_valid_reg(reg_num2) &&
		is_valid_reg(reg_num3))
	{
		process->reg[reg_num3] = process->reg[reg_num] - process->reg[reg_num2];
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + 4) % MEM_SIZE;
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
	m->player[process->owner - 1].process_count++;
	ft_lstadd(&(m->player[process->owner - 1].process_list),
		ft_lstnew(&process, sizeof(t_process)));
	process->pc = (process->pc + 3) % MEM_SIZE;
}

void		do_lld(t_process *process, t_master *m)
{
	unsigned char	reg_num;

	if (validate_args(process, m))
	{
		reg_num = m->core[(process->pc + 2) % MEM_SIZE].value - 1;
		process->reg[reg_num] = read_larg(process, m, 1);
		process->carry = (process->reg[reg_num] == 0);
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}

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
	m->player[process->owner - 1].process_count++;
	ft_lstadd(&(m->player[process->owner - 1].process_list),
		ft_lstnew(&process, sizeof(t_process)));
	process->pc = (process->pc + 3) % MEM_SIZE;
}

void		append_afflog(unsigned int reg_num, t_process *process, t_master *m)
{
	char	*afflog;
	int		i;

	afflog = m->player[process->owner - 1].afflog;
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
		afflog[i] =afflog[i + 1];
	afflog[i] = process->reg[reg_num] % 256;
}

void		do_aff(t_process *process, t_master *m)
{
	if (validate_args(process, m))
		append_afflog(read_arg_exact(process, m, 0), process, m);
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}
