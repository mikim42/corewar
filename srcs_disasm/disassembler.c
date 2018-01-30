/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 22:10:39 by apuel             #+#    #+#             */
/*   Updated: 2018/01/29 22:10:41 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

void	write_byteswapped(void *dst, void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[n - i - 1];
		i++;
	}
}

size_t	print_instruction(unsigned char *code)
{
	unsigned char	index;
	unsigned char	type;
	unsigned int	pos;
	unsigned int	i;

	index = code[0] - 1;
	ft_printf("%s ", g_op_tab[index].mnemonic);
	pos = (g_op_tab[index].type_byte) ? 2 : 1;
	i = 0;
	while (i < g_op_tab[index].num_args)
	{
		type = get_type(index, code, i);
		if (type == REG_CODE)
			ft_printf("r%hhu", code[pos]);
		else if (type == IND_CODE)
			ft_printf("%hd", ((short)code[pos] << 8) | (short)code[pos + 1]);
		else if (type == DIR_CODE && g_op_tab[index].short_dir)
			ft_printf("%%%hd", ((short)code[pos] << 8) | (short)code[pos + 1]);
		else if (type == DIR_CODE)
			ft_printf("%%%d", (int)code[pos + 3] | ((int)code[pos + 2] << 8) |
						((int)code[pos + 1] << 16) | ((int)code[pos] << 24));
		pos += count_bytes(type, g_op_tab[index].short_dir);
		ft_printf("%s", ++i == g_op_tab[index].num_args ? "\n" : ", ");
	}
	return (pos);
}

void	disassemble(t_program *program)
{
	size_t			i;
	unsigned int	prog_size;

	write_byteswapped(&prog_size, &(program->header.prog_size), 4);
	ft_printf(PROGRAM_HEADER, program->header.prog_name);
	ft_printf(".name \"%s\"\n", program->header.prog_name);
	ft_printf(".comment \"%s\"\n\n", program->header.comment);
	i = 0;
	while (i < prog_size)
	{
		if (program->code[i] == 0 || program->code[i] > 16 ||
			i == prog_size - 1 ||
			i + instruction_length(&(program->code[i])) > prog_size ||
			!validate_args(&(program->code[i])))
		{
			ft_printf("# Invalid instruction @ .text:%08lX (0x%02X)\n",
				i, program->code[i]);
			i++;
		}
		else
			i += print_instruction(&(program->code[i]));
	}
}
