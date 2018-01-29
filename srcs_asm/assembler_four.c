/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler_four.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 22:35:20 by mikim             #+#    #+#             */
/*   Updated: 2018/01/28 16:38:02 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

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

long		dir_ext(char *argument, t_asm_ctx *ctx,
						t_program *program, t_list *labels)
{
	int	i;

	if (g_op_tab[ctx->op].type_byte)
		ctx->code[1] |= DIR_CODE << (2 * (3 - ctx->arg));
	if (argument[1] == LABEL_CHAR)
	{
		if (label_arg(&argument[2], program, labels, &i) < 0)
			return (-1);
	}
	else
	{
		i = 2;
		while (ft_isdigit(argument[i]))
			i++;
		if (argument[i])
			return (throw_verr(BAD_DIRECT, (long)argument, 0, 0));
		i = ft_atoi(&argument[1]);
	}
	write_byteswapped(&(ctx->code[ctx->pc]), &i,
			g_op_tab[ctx->op].short_dir ? 2 : 4);
	ctx->pc += g_op_tab[ctx->op].short_dir ? 2 : 4;
	return (1);
}

long		dir_arg(char *argument, t_asm_ctx *ctx,
						t_program *program, t_list *labels)
{
	if (argument[0] == DIRECT_CHAR)
	{
		if (!(g_op_tab[ctx->op].arg_types[ctx->arg] & T_DIR))
		{
			return (throw_verr(INVALID_DIR,
					(long)g_op_tab[ctx->op].mnemonic, ctx->arg + 1, 0));
		}
		if (argument[1] != '-' && argument[1] != '+' &&
			!ft_isdigit(argument[1]) && argument[1] != LABEL_CHAR)
			return (throw_verr(BAD_DIRECT, (long)argument, 0, 0));
		return (dir_ext(argument, ctx, program, labels));
	}
	return (0);
}

long		ind_ext(char *argument, t_asm_ctx *ctx,
						t_program *program, t_list *labels)
{
	int	i;

	i = 2 * (3 - ctx->arg);
	if (g_op_tab[ctx->op].type_byte)
		ctx->code[1] |= IND_CODE << i;
	if (argument[0] == LABEL_CHAR)
	{
		if (label_arg(&argument[1], program, labels, &i) < 0)
			return (-1);
	}
	else
	{
		i = 1;
		while (ft_isdigit(argument[i]))
			i++;
		if (argument[i])
			return (throw_verr(BAD_DIRECT, (long)argument, 0, 0));
		i = ft_atoi(argument);
	}
	write_byteswapped(&(ctx->code[ctx->pc]), &i, 2);
	ctx->pc += 2;
	return (1);
}

long		ind_arg(char *argument, t_asm_ctx *ctx,
						t_program *program, t_list *labels)
{
	if (argument[0] == '-' || argument[0] == '+' ||
			ft_isdigit(argument[0]) || argument[0] == LABEL_CHAR)
	{
		if (!(g_op_tab[ctx->op].arg_types[ctx->arg] & T_IND))
		{
			return (throw_verr(INVALID_DIR,
						(long)g_op_tab[ctx->op].mnemonic, ctx->arg + 1, 0));
		}
		return (ind_ext(argument, ctx, program, labels));
	}
	return (0);
}
