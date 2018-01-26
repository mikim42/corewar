/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:09:54 by apuel             #+#    #+#             */
/*   Updated: 2018/01/25 21:32:50 by mikim            ###   ########.fr       */
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
			return (throw_verr(INVALID_REG,
						(long)g_op_tab[ctx->op].mnemonic, ctx->arg + 1, 0));
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
			return (throw_verr(INVALID_DIR,
					(long)g_op_tab[ctx->op].mnemonic, ctx->arg + 1, 0));
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
		if (!(g_op_tab[ctx->op].arg_types[ctx->arg] & T_IND))
			return (throw_verr(INVALID_DIR,
					(long)g_op_tab[ctx->op].mnemonic, ctx->arg + 1, 0));
		return (ind_ext(argument, ctx, program, labels));
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
		return (throw_verr(NOT_ENOUGH_ARG,
					(long)g_op_tab[ctx->op].mnemonic, 0, 0));
	else if (ctx->arg >= g_op_tab[ctx->op].num_args &&
			assembly[*i + 1] && assembly[*i + 1][0] == SEPARATOR_CHAR)
		return (throw_verr(TOO_MANY_ARG,
					(long)g_op_tab[ctx->op].mnemonic, 0, 0));
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
				ft_memcpy(&program->code[program->header.prog_size],
						ctx.code, ctx.pc);
			return (ctx.pc);
		}
	return (throw_verr(INVALID_INST, (long)assembly[*i], 0, 0));
}

t_program	*init_program(char **assembly, t_program *program, t_list **labels)
{
	size_t		i;
	size_t		pc;
	int			error;
	t_list		*label;
	t_program	*resize;

	i = 0;
	pc = 0;
	*labels = 0;
	while (assembly[i])
	{
		error = assemble(assembly, &i, 0, 0);
		if (error < 0)
		{
			ft_lstdel(labels, (void (*)(void *, size_t))free);
			return (program);
		}
		if (!error)
		{
			label = *labels;
			while (label)
			{
				if (!ft_strcmp(label->content, assembly[i]))
				{
					ft_lstdel(labels, (void (*)(void *, size_t))free);
					throw_verr("Duplicate label, '%s'!", (long)assembly[i], 0, 0);
					return (program);
				}
				label = label->next;
			}
			if (!(label = ft_lstnew(assembly[i], ft_strlen(assembly[i]) + 1)))
			{
				ft_lstdel(labels, (void (*)(void *, size_t))free);
				throw_error("Failed to allocate memory!", 0);
				return (program);
			}
			i++;
			label->content_size = pc;
			ft_lstadd(labels, label);
		}
		pc += (unsigned int)error;
	}
	if ((resize = realloc(program, sizeof(t_program) + pc)))
	{
		program = resize;
		ft_bzero(((char *)program) + sizeof(t_program), pc);
		program->header.magic = ((COREWAR_EXEC_MAGIC & 0xFF) << 24) |
								((COREWAR_EXEC_MAGIC & 0xFF00) << 8) |
								((COREWAR_EXEC_MAGIC & 0xFF0000) >> 8) |
								((COREWAR_EXEC_MAGIC & 0xFF000000) >> 24);
	}
	else
	{
		ft_lstdel(labels, (void (*)(void *, size_t))free);
		throw_error("Failed to allocate memory!", 0);
	}
	return (program);
}

t_program	*the_assemble_everything_function(char *source)
{
	t_program	*program;
	char		**assembly;
	t_list		*labels;
	size_t		i;
	int			error;

	i = 0;
	if ((program = ft_memalloc(sizeof(t_program))))
		if ((assembly = parse_source(source, program)))
		{
			program = init_program(assembly, program, &labels);
			if (program->header.magic)
				while (program && assembly[i])
				{
					error = assemble(assembly, &i, program, labels);
					if (error >= 0)
					{
						if (!error)
							i++;
						program->header.prog_size += error;
					}
					else
						ft_memdel((void **)&program);
				}
			else
				ft_memdel((void **)&program);
			ft_lstdel(&labels, (void (*)(void *, size_t))free);
			i = 0;
			while (assembly[i])
				free(assembly[i++]);
			free(assembly);
		}
		else
			ft_memdel((void **)&program);
	else
		throw_error("Failed to allocate memory!", 0);
	return (program);
}
