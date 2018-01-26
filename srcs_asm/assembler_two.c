/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 22:34:45 by mikim             #+#    #+#             */
/*   Updated: 2018/01/25 22:41:02 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void		write_byteswapped(void *dst, void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[n - i - 1];
		i++;
	}
}

long		preprocess(char *source, char *ref, char *dst, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!ft_strncmp(source, ref, ft_strlen(ref)))
	{
		ft_memset(source, ' ', (i = ft_strlen(ref)));
		while (source[i] && (source[i] == ' ' || source[i] == '\t'))
			i++;
		if (source[i] != '"')
			return (throw_verr(INVALID_ERR, (long)ref, 0, 0));
		j = 0;
		source[i++] = ' ';
		ft_bzero(dst, size + 1);
		while (source[i] && source[i] != '"')
		{
			if (j < size)
				dst[j++] = source[i];
			source[i++] = ' ';
		}
		if (!source[i])
			return (throw_verr(EOF_ERR, (long)ref, 0, 0));
		source[i++] = ' ';
	}
	return (i);
}

char		**parse_source(char *source, t_program *program)
{
	size_t	i;
	long	result;

	i = -1;
	while (source[++i])
	{
		result = preprocess(&source[i], NAME_CMD_STRING,
				program->header.prog_name, PROG_NAME_LENGTH);
		if (result == -1)
			return (0);
		i += (size_t)result;
		result = preprocess(&source[i], COMMENT_CMD_STRING,
				program->header.comment, COMMENT_LENGTH);
		if (result < 0)
			return (0);
		i += (size_t)result;
		if (source[i] == COMMENT_CHAR || source[i] == COMMENT_ALT)
			while (source[i] && source[i] != '\n')
				source[i++] = ' ';
		if (!source[i])
			break ;
	}
	return (split_syntax(source));
}

long		reg_arg(char *argument, t_asm_ctx *ctx)
{
	size_t	i;

	if (argument[0] == 'r' || argument[0] == 'R')
	{
		if (!(g_op_tab[ctx->op].arg_types[ctx->arg] & T_REG))
		{
			return (throw_verr(INVALID_REG,
						(long)g_op_tab[ctx->op].mnemonic, ctx->arg + 1, 0));
		}
		i = 2 * (3 - ctx->arg);
		if (g_op_tab[ctx->op].type_byte)
			ctx->code[1] |= REG_CODE << i;
		ctx->code[(ctx->pc)++] = (unsigned char)ft_atoi(&argument[1]);
		i = 1;
		while (ft_isdigit(argument[i]))
			i++;
		if (argument[i])
			return (throw_verr(BAD_REG, (long)argument, 0, 0));
		return (1);
	}
	return (0);
}

long		label_arg(char *argument, t_program *program,
							t_list *labels, int *result)
{
	t_list	*label;
	size_t	len;

	*result = 0;
	if (program)
	{
		label = labels;
		len = ft_strlen(argument);
		while (label &&
				(ft_strncmp(label->content, argument, len) ||
				((char *)label->content)[len] != LABEL_CHAR))
			label = label->next;
		if (label)
			*result = label->content_size - program->header.prog_size;
		else
			return (throw_verr(UNDEF_LABEL, (long)argument, 0, 0));
	}
	return (0);
}
