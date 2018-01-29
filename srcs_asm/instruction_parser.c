/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 22:35:53 by mikim             #+#    #+#             */
/*   Updated: 2018/01/28 16:38:03 by mikim            ###   ########.fr       */
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

long		check_arg(char *assem, t_asm_ctx *ctx,
						t_program *program, t_list *labels)
{
	long	res;

	if ((res = reg_arg(assem, ctx)) ||
		(res = dir_arg(assem, ctx, program, labels)) ||
		(res = ind_arg(assem, ctx, program, labels)))
		return (res);
	return (0);
}

long		assemble_instruction(char **assembly, size_t *i,
									t_asm_ctx *ctx, t_program *program)
{
	long	res;

	if (!(res = check_arg(assembly[*i], ctx, program, ctx->labels)))
		return (throw_verr(UNKNOWN_ARG, (long)assembly[*i], 0, 0));
	if (res < 0)
		return (res);
	(ctx->arg)++;
	if (ctx->arg < g_op_tab[ctx->op].num_args &&
			(!assembly[*i + 1] || assembly[*i + 1][0] != SEPARATOR_CHAR))
	{
		return (throw_verr(NOT_ENOUGH_ARG,
					(long)g_op_tab[ctx->op].mnemonic, 0, 0));
	}
	else if (ctx->arg >= g_op_tab[ctx->op].num_args &&
			assembly[*i + 1] && assembly[*i + 1][0] == SEPARATOR_CHAR)
	{
		return (throw_verr(TOO_MANY_ARG,
					(long)g_op_tab[ctx->op].mnemonic, 0, 0));
	}
	if (ctx->arg < g_op_tab[ctx->op].num_args)
		(*i)++;
	return (0);
}

long		assemble(char **assembly, size_t *i,
						t_program *program, t_list *labels)
{
	t_asm_ctx	ctx;
	long		res;

	ft_bzero(&ctx, sizeof(t_asm_ctx));
	res = ft_strlen(assembly[*i]);
	if (res && assembly[*i][res - 1] == LABEL_CHAR)
		return (0);
	ctx.op = -1;
	ctx.labels = labels;
	while (g_op_tab[++(ctx.op)].mnemonic)
		if (!ft_strcmp(assembly[*i], g_op_tab[ctx.op].mnemonic))
		{
			ctx.code[(ctx.pc)++] = g_op_tab[ctx.op].opcode;
			(g_op_tab[ctx.op].type_byte) ? (ctx.pc)++ : 0;
			while (assembly[++(*i)] && ctx.arg < g_op_tab[ctx.op].num_args)
				if (assemble_instruction(assembly, i, &ctx, program) < 0)
					return (-1);
			if (ctx.arg < g_op_tab[ctx.op].num_args)
				return (throw_error(FILE_ABRUPT, -1));
			if (program)
				ft_memcpy(&(program->code[program->header.prog_size]),
						ctx.code, ctx.pc);
			return (ctx.pc);
		}
	return (throw_verr(INVALID_INST, (long)assembly[*i], 0, 0));
}
