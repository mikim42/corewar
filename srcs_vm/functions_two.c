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

unsigned char	get_type(t_process *process, unsigned int i)
{
	return ((process->icache[1] >> (2 * (3 - i))) & 3);
}

int				read_reg_exact(t_process *process,
								t_master *m, unsigned int arg)
{
	unsigned char	opcode;
	unsigned char	type;
	unsigned int	pos;
	unsigned int	i;

	opcode = process->icache[0];
	pos = 2;
	i = 0;
	while (i < arg)
	{
		type = get_type(process, i++);
		pos += count_bytes(type, g_op_tab[opcode - 1].short_dir);
	}
	type = get_type(process, arg);
	if (type == REG_CODE)
		return (process->icache[pos] - 1);
	else if (type == IND_CODE)
		return (read_int(m, ((int)process->pc +
				(cached_short(process, pos) % IDX_MOD))));
	else if (type == DIR_CODE && g_op_tab[opcode - 1].short_dir)
		return (cached_short(process, pos));
	else if (type == DIR_CODE)
		return (cached_int(process, pos));
	return (0);
}

int				read_ind_exact(t_process *process,
								t_master *m, unsigned int arg)
{
	unsigned char	opcode;
	unsigned char	type;
	unsigned int	pos;
	unsigned int	i;

	(void)m;
	opcode = process->icache[0];
	pos = 2;
	i = 0;
	while (i < arg)
	{
		type = get_type(process, i++);
		pos += count_bytes(type, g_op_tab[opcode - 1].short_dir);
	}
	type = get_type(process, arg);
	if (type == REG_CODE)
		return (process->reg[process->icache[pos] - 1]);
	else if (type == IND_CODE)
		return (cached_short(process, pos));
	else if (type == DIR_CODE && g_op_tab[opcode - 1].short_dir)
		return (cached_short(process, pos));
	else if (type == DIR_CODE)
		return (cached_int(process, pos));
	return (0);
}

int				read_arg(t_process *process, t_master *m, unsigned int arg)
{
	unsigned char	opcode;
	unsigned char	type;
	unsigned int	pos;
	unsigned int	i;

	opcode = process->icache[0];
	pos = 2;
	i = 0;
	while (i < arg)
	{
		type = get_type(process, i++);
		pos += count_bytes(type, g_op_tab[opcode - 1].short_dir);
	}
	type = get_type(process, arg);
	if (type == REG_CODE)
		return (process->reg[process->icache[pos] - 1]);
	else if (type == IND_CODE)
		return (read_int(m, ((int)process->pc +
				(cached_short(process, pos) % IDX_MOD))));
	else if (type == DIR_CODE && g_op_tab[opcode - 1].short_dir)
		return (cached_short(process, pos));
	else if (type == DIR_CODE)
		return (cached_int(process, pos));
	return (0);
}

int				read_larg(t_process *process, t_master *m, unsigned int arg)
{
	unsigned char	opcode;
	unsigned char	type;
	unsigned int	pos;
	unsigned int	i;

	opcode = process->icache[0];
	pos = 2;
	i = 0;
	while (i < arg)
	{
		type = get_type(process, i++);
		pos += count_bytes(type, g_op_tab[opcode - 1].short_dir);
	}
	type = get_type(process, arg);
	if (type == REG_CODE)
		return (process->reg[process->icache[pos] - 1]);
	else if (type == IND_CODE)
		return (read_int(m, ((int)process->pc +
				cached_short(process, pos))));
	else if (type == DIR_CODE && g_op_tab[opcode - 1].short_dir)
		return (cached_short(process, pos));
	else if (type == DIR_CODE)
		return (cached_int(process, pos));
	return (0);
}
