/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 18:42:45 by mikim             #+#    #+#             */
/*   Updated: 2018/01/27 03:06:14 by ashih            ###   ########.fr       */
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
