/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:09:54 by apuel             #+#    #+#             */
/*   Updated: 2018/01/23 14:09:57 by apuel            ###   ########.fr       */
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

char		**parse_source(char *source, t_program *program)
{
	size_t			i;
	size_t			j;

	i = -1;
	while (source[++i])
	{
		if (!ft_strncmp(&source[i], NAME_CMD_STRING, sizeof(NAME_CMD_STRING) - 1))
		{
			j = 0;
			while (j++ < sizeof(NAME_CMD_STRING) - 1)
				source[i++] = ' ';
			while (source[i] && (source[i] == ' ' || source[i] == '\t'))
				i++;
			if (source[i] != '"')
				return ((char **)throw_error("Found '.name', but there isn't a name!", 0));
			j = 0;
			source[i++] = ' ';
			ft_bzero(program->header.prog_name, PROG_NAME_LENGTH);
			while (source[i] && source[i] != '"')
			{
				if (j < PROG_NAME_LENGTH)
					program->header.prog_name[j++] = source[i];
				source[i++] = ' ';
			}
			if (!source[i])
				return ((char **)throw_error("'.name' is interrupted by an EOF!", 0));
			source[i++] = ' ';
		}
		if (!ft_strncmp(&source[i], COMMENT_CMD_STRING, sizeof(COMMENT_CMD_STRING) - 1))
		{
			j = 0;
			while (j++ < sizeof(COMMENT_CMD_STRING) - 1)
				source[i++] = ' ';
			while (source[i] && (source[i] == ' ' || source[i] == '\t'))
				i++;
			if (source[i] != '"')
				return ((char **)throw_error("Found '.comment', but there isn't a comment!", 0));
			j = 0;
			source[i++] = ' ';
			ft_bzero(program->header.comment, COMMENT_LENGTH);
			while (source[i] && source[i] != '"')
			{
				if (j < COMMENT_LENGTH)
					program->header.comment[j++] = source[i];
				source[i++] = ' ';
			}
			if (!source[i])
				return ((char **)throw_error("'.comment' is interrupted by an EOF!", 0));
			source[i++] = ' ';
		}
		if (source[i] == COMMENT_CHAR || source[i] == COMMENT_ALT)
			while (source[i] && source[i] != '\n')
				source[i++] = ' ';
		if (!source[i])
			break ;
	}
	return (split_syntax(source));
}

int			assemble(char **assembly, size_t *i, t_program *program, t_list *labels)
{
	unsigned char	code[0x10];
	t_list			*label;
	size_t			arg;
	size_t			pc;
	size_t			j;
	size_t			k;

	ft_bzero(code, 0x10);
	k = ft_strlen(assembly[*i]);
	if (!k || assembly[*i][k - 1] == LABEL_CHAR)
		return (0);
	j = -1;
	pc = 0;
	while (g_op_tab[++j].mnemonic)
		if (!ft_strcmp(assembly[*i], g_op_tab[j].mnemonic))
		{
			code[pc++] = g_op_tab[j].opcode;
			if (g_op_tab[j].type_byte)
				pc++;
			arg = 0;
			while (assembly[++(*i)] && arg < g_op_tab[j].num_args)
			{
				if (assembly[*i][0] == 'r' || assembly[*i][0] == 'R')
				{
					if (!(g_op_tab[j].arg_types[arg] & T_REG))
						return (throw_verbose_error("Invalid type 'REG' for %s, argument %li!", (long)g_op_tab[j].mnemonic, arg + 1, 0));
					k = 2 * (3 - arg);
					if (g_op_tab[j].type_byte)
						code[1] |= REG_CODE << k;
					code[pc++] = (unsigned char)ft_atoi(&assembly[*i][1]);
					k = 1;
					while (ft_isdigit(assembly[*i][k]))
						k++;
					if (assembly[*i][k])
						return (throw_verbose_error("Bad 'REG' value |%s|!", (long)assembly[*i], 0, 0));
				}
				else if (assembly[*i][0] == DIRECT_CHAR)
				{
					if (!(g_op_tab[j].arg_types[arg] & T_DIR))
						return (throw_verbose_error("Invalid type 'DIRECT' for %s, argument %li!", (long)g_op_tab[j].mnemonic, arg + 1, 0));
					k = 2 * (3 - arg);
					if (g_op_tab[j].type_byte)
						code[1] |= DIR_CODE << k;
					if (assembly[*i][1] == LABEL_CHAR)
					{
						k = 0;
						if (program)
						{
							label = labels;
							k = ft_strlen(&assembly[*i][2]);
							while (label && (ft_strncmp(label->content, &assembly[*i][2], k) || ((char *)label->content)[k] != LABEL_CHAR))
								label = label->next;
							if (label)
								k = label->content_size - program->header.prog_size;
							else
								return (throw_verbose_error("Undefined 'DIRECT' label '%s'!", (long)&assembly[*i][2], 0, 0));
						}
					}
					else
					{
						k = 1;
						if (assembly[*i][k] == '-' || assembly[*i][k] == '+')
							k++;
						while (ft_isdigit(assembly[*i][k]))
							k++;
						if (assembly[*i][k])
							return (throw_verbose_error("Bad 'DIRECT' value |%s|!", (long)assembly[*i], 0, 0));
						k = ft_atoi(&assembly[*i][1]);
					}
					write_byteswapped(&code[pc], &k, g_op_tab[j].short_dir ? 2 : 4);
					pc += g_op_tab[j].short_dir ? 2 : 4;
				}
				else if (assembly[*i][0] == '-' || assembly[*i][0] == '+' ||
						ft_isdigit(assembly[*i][0]) || assembly[*i][0] == LABEL_CHAR)
				{
					if (!(g_op_tab[j].arg_types[arg] & T_IND))
						return (throw_verbose_error("Invalid type 'INDIRECT' for %s, argument %li!", (long)g_op_tab[j].mnemonic, arg + 1, 0));
					k = 2 * (3 - arg);
					if (g_op_tab[j].type_byte)
						code[1] |= IND_CODE << k;
					if (assembly[*i][0] == LABEL_CHAR)
					{
						k = 0;
						if (program)
						{
							label = labels;
							k = ft_strlen(&assembly[*i][1]);
							while (label && (ft_strncmp(label->content, &assembly[*i][1], k) || ((char *)label->content)[k] != LABEL_CHAR))
								label = label->next;
							if (label)
								k = label->content_size - program->header.prog_size;
							else
								return (throw_verbose_error("Undefined 'INDIRECT' label '%s'!", (long)&assembly[*i][1], 0, 0));
						}
					}
					else
					{
						k = 1;
						while (ft_isdigit(assembly[*i][k]))
							k++;
						if (assembly[*i][k])
							return (throw_verbose_error("Bad 'INDIRECT' value |%s|!", (long)assembly[*i], 0, 0));
						k = ft_atoi(assembly[*i]);
					}
					write_byteswapped(&code[pc], &k, 2);
					pc += 2;
				}
				else
					return (throw_verbose_error("Unknown arguement |%s|!", (long)assembly[*i], 0, 0));
				arg++;
				k = ft_strlen(assembly[*i]);
				if (arg < g_op_tab[j].num_args && (!assembly[*i + 1] || assembly[*i + 1][0] != SEPARATOR_CHAR))
					return (throw_verbose_error("Not enough arguements for %s!", (long)g_op_tab[j].mnemonic, 0, 0));
				else if (arg >= g_op_tab[j].num_args && assembly[*i + 1] && assembly[*i + 1][0] == SEPARATOR_CHAR)
					return (throw_verbose_error("Too many arguements for %s!", (long)g_op_tab[j].mnemonic, 0, 0));
				if (arg < g_op_tab[j].num_args)
					(*i)++;
			}
			if (arg < g_op_tab[j].num_args)
				return (throw_error("File ended abruptly!", -1));
			break ;
		}
	if (!g_op_tab[j].mnemonic)
		return (throw_verbose_error("Invalid instruction |%s|!", (long)assembly[*i], 0, 0));
	if (program)
		ft_memcpy(&program->code[program->header.prog_size], code, pc);
	return (pc);
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
					throw_verbose_error("Duplicate label, '%s'!", (long)assembly[i], 0, 0);
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
	{
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
	}
	else
		throw_error("Failed to allocate memory!", 0);
	return (program);
}
