/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler_four.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 22:35:53 by mikim             #+#    #+#             */
/*   Updated: 2018/01/25 22:36:23 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

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

t_list		*create_label(char **assembly, t_list **labels, size_t i, size_t pc)
{
	t_list	*label;

	if (!is_valid_label(assembly[i]))
	{
		ft_lstdel(labels, (void (*)(void *, size_t))free);
		throw_verr(INVALID_LABEL, (long)assembly[i], 0, 0);
		return (NULL);
	}
	label = *labels;
	while (label)
	{
		if (!ft_strcmp(label->content, assembly[i]))
		{
			ft_lstdel(labels, (void (*)(void *, size_t))free);
			throw_verr(DUP_LABEL, (long)assembly[i], 0, 0);
			return (NULL);
		}
		label = label->next;
	}
	if (!(label = ft_lstnew(assembly[i], ft_strlen(assembly[i]) + 1)))
		throw_error(ALLOC_FAIL, 0);
	if (!label)
		ft_lstdel(labels, (void (*)(void *, size_t))free);
	label ? label->content_size = pc : (void)0;
	return (label);
}

t_program	*resize_program(t_program *program, t_list **labels, size_t pc)
{
	t_program	*resize;
	size_t		magic;

	if ((resize = realloc(program, sizeof(t_program) + pc)))
	{
		program = resize;
		ft_bzero(((char *)program) + sizeof(t_program), pc);
		magic = COREWAR_EXEC_MAGIC;
		write_byteswapped(&(program->header.magic), &magic, 4);
	}
	else
	{
		ft_lstdel(labels, (void (*)(void *, size_t))free);
		throw_error(ALLOC_FAIL, 0);
	}
	return (program);
}

t_program	*init_program(char **assembly, t_program *program,
							t_list **labels, size_t pc)
{
	t_list		*label;
	int			error;
	size_t		i;

	i = 0;
	*labels = NULL;
	while (assembly[i])
	{
		if ((error = assemble(assembly, &i, 0, 0)) < 0)
		{
			ft_lstdel(labels, (void (*)(void *, size_t))free);
			return (program);
		}
		if (error && (pc += (unsigned int)error))
			continue ;
		if (!(label = create_label(assembly, labels, i, pc)))
			return (program);
		i++;
		ft_lstadd(labels, label);
	}
	return (resize_program(program, labels, pc));
}
