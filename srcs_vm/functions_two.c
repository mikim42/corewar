/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 18:08:50 by mikim             #+#    #+#             */
/*   Updated: 2018/01/26 20:10:54 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned char	get_type(t_process *process, t_master *m, unsigned int i)
{
	unsigned char	type;

	type = m->core[(process->pc + 1) % MEM_SIZE].value;
	type = (type >> (2 * (3 - i))) & 3;
	return (type);
}

int				read_reg_exact(t_process *process,
								t_master *m, unsigned int arg)
{
	unsigned char	opcode;
	unsigned char	type;
	unsigned int	pos;
	unsigned int	i;

	opcode = process->opcode;
	pos = 2;
	i = 0;
	while (i < arg)
	{
		type = get_type(process, m, i++);
		pos += count_bytes(type, g_op_tab[opcode - 1].short_dir);
	}
	type = get_type(process, m, arg);
	if (type == REG_CODE)
		return (m->core[(process->pc + pos) % MEM_SIZE].value - 1);
	else if (type == IND_CODE)
		return (read_short(m, ((int)process->pc +
				(read_short(m, process->pc + pos) % IDX_MOD))));
	else if (type == DIR_CODE && g_op_tab[opcode - 1].short_dir)
		return (read_short(m, process->pc + pos));
	else if (type == DIR_CODE)
		return (read_int(m, process->pc + pos));
	return (0);
}

int				read_ind_exact(t_process *process,
								t_master *m, unsigned int arg)
{
	unsigned char	opcode;
	unsigned char	type;
	unsigned int	p;
	unsigned int	i;

	opcode = process->opcode;
	p = 2;
	i = 0;
	while (i < arg)
	{
		type = get_type(process, m, i++);
		p += count_bytes(type, g_op_tab[opcode - 1].short_dir);
	}
	type = get_type(process, m, arg);
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

int				read_arg(t_process *process, t_master *m, unsigned int arg)
{
	unsigned char	opcode;
	unsigned char	type;
	unsigned int	p;
	unsigned int	i;

	opcode = process->opcode;
	p = 2;
	i = 0;
	while (i < arg)
	{
		type = get_type(process, m, i++);
		p += count_bytes(type, g_op_tab[opcode - 1].short_dir);
	}
	type = get_type(process, m, arg);
	if (type == REG_CODE)
		return (process->reg[m->core[(process->pc + p) % MEM_SIZE].value - 1]);
	else if (type == IND_CODE)
		return (read_short(m, ((int)process->pc +
				(read_short(m, process->pc + p) % IDX_MOD))));
	else if (type == DIR_CODE && g_op_tab[opcode - 1].short_dir)
		return (read_short(m, process->pc + p));
	else if (type == DIR_CODE)
		return (read_int(m, process->pc + p));
	return (0);
}

int				read_larg(t_process *process, t_master *m, unsigned int arg)
{
	unsigned char	opcode;
	unsigned char	type;
	unsigned int	p;
	unsigned int	i;

	opcode = process->opcode;
	p = 2;
	i = 0;
	while (i < arg)
	{
		type = get_type(process, m, i++);
		p += count_bytes(type, g_op_tab[opcode - 1].short_dir);
	}
	type = get_type(process, m, arg);
	if (type == REG_CODE)
		return (process->reg[m->core[(process->pc + p) % MEM_SIZE].value - 1]);
	else if (type == IND_CODE)
		return (read_short(m, ((int)process->pc +
				read_short(m, process->pc + p))));
	else if (type == DIR_CODE && g_op_tab[opcode - 1].short_dir)
		return (read_short(m, process->pc + p));
	else if (type == DIR_CODE)
		return (read_int(m, process->pc + p));
	return (0);
}
