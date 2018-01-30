/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <apuel@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 18:42:45 by apuel             #+#    #+#             */
/*   Updated: 2018/01/28 19:51:03 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

size_t			count_bytes(unsigned char arg_code, int short_dir)
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

unsigned char	get_type(unsigned char op, unsigned char *code, unsigned int i)
{
	if (g_op_tab[op].type_byte)
		return ((code[1] >> (2 * (3 - i))) & 3);
	if (g_op_tab[op].arg_types[i] == T_REG)
		return (REG_CODE);
	if (g_op_tab[op].arg_types[i] == T_IND)
		return (IND_CODE);
	if (g_op_tab[op].arg_types[i] == T_DIR)
		return (DIR_CODE);
	return (0);
}

int				validate_args(unsigned char *code)
{
	unsigned char	index;
	unsigned char	type;
	unsigned int	pos;
	unsigned int	i;

	index = code[0] - 1;
	pos = (g_op_tab[index].type_byte) ? 2 : 1;
	i = 0;
	while (i < g_op_tab[index].num_args)
	{
		type = get_type(index, code, i);
		if ((type == REG_CODE && !(g_op_tab[index].arg_types[i] & T_REG)) ||
			(type == DIR_CODE && !(g_op_tab[index].arg_types[i] & T_DIR)) ||
			(type == IND_CODE && !(g_op_tab[index].arg_types[i] & T_IND)) ||
			!type)
			return (0);
		pos += count_bytes(type, g_op_tab[index].short_dir);
		i++;
	}
	return (1);
}

size_t			instruction_length(unsigned char *code)
{
	unsigned char	index;
	unsigned char	type;
	unsigned int	i;
	size_t			length;

	index = code[0] - 1;
	length = (g_op_tab[index].type_byte) ? 2 : 1;
	i = 0;
	while (i < g_op_tab[index].num_args)
	{
		type = get_type(index, code, i++);
		length += count_bytes(type, g_op_tab[index].short_dir);
	}
	return (length);
}
