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

#include "libft.h"
#include "op_ext.h"

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
			while (j++ < sizeof(NAME_CMD_STRING))
				source[i++] = ' ';
			while (source[i] && source[i] == ' ')
				i++;
			if (source[i] != '"')
				return ((char **)(long)ft_puterror("Found '.name', but there isn't a name!\n", 0));
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
				return ((char **)(long)ft_puterror("'.name' is interrupted by an EOF!\n", 0));
			source[i++] = ' ';
		}
		if (!ft_strncmp(&source[i], COMMENT_CMD_STRING, sizeof(COMMENT_CMD_STRING) - 1))
		{
			j = 0;
			while (j++ < sizeof(COMMENT_CMD_STRING))
				source[i++] = ' ';
			while (source[i] && source[i] == ' ')
				i++;
			if (source[i] != '"')
				return ((char **)(long)ft_puterror("Found '.comment', but there isn't a comment!\n", 0));
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
				return ((char **)(long)ft_puterror("'.comment' is interrupted by an EOF!\n", 0));
			source[i++] = ' ';
		}
		if (source[i] == COMMENT_CHAR || source[i] == COMMENT_ALT)
			while (source[i] && source[i] != '\n')
				source[i++] = ' ';
		if (source[i] == '\n' || source[i] == '\t')
			source[i] = ' ';
		if (!source[i])
			break ;
	}
	return (ft_strsplit(source, ' '));
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
						return (-1);
					k = 2 * (3 - arg);
					if (g_op_tab[j].type_byte)
						code[1] |= REG_CODE << k;
					code[pc++] = (unsigned char)ft_atoi(&assembly[*i][1]);
					k = 1;
					while (ft_isdigit(assembly[*i][k]))
						k++;
					if (assembly[*i][k] && (assembly[*i][k] != SEPARATOR_CHAR || assembly[*i][k + 1]))
						return (-2);
				}
				else if (assembly[*i][0] == DIRECT_CHAR)
				{
					if (!(g_op_tab[j].arg_types[arg] & T_DIR))
						return (-3);
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
							if (assembly[*i][k + 1] == SEPARATOR_CHAR)
								k--;
							while (label && ft_strncmp(label->content, &assembly[*i][2], k))
								label = label->next;
							if (label)
								k = label->content_size - program->header.prog_size;
							else
								return (-4);
						}
					}
					else
					{
						k = 1;
						if (assembly[*i][k] == '-' || assembly[*i][k] == '+')
							k++;
						while (ft_isdigit(assembly[*i][k]))
							k++;
						if (assembly[*i][k] && (assembly[*i][k] != SEPARATOR_CHAR || assembly[*i][k + 1]))
							return (-5);
						k = ft_atoi(&assembly[*i][1]);
					}
					write_byteswapped(&code[pc], &k, g_op_tab[j].short_dir ? 2 : 4);
					pc += g_op_tab[j].short_dir ? 2 : 4;
				}
				else if (assembly[*i][0] == '-' || assembly[*i][0] == '+' ||
						ft_isdigit(assembly[*i][0]) || assembly[*i][0] == LABEL_CHAR)
				{
					if (!(g_op_tab[j].arg_types[arg] & T_IND))
						return (-6);
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
							if (assembly[*i][k] == SEPARATOR_CHAR)
								k--;
							while (label && ft_strncmp(label->content, &assembly[*i][1], k))
								label = label->next;
							if (label)
								k = label->content_size - program->header.prog_size;
							else
								return (-7);
						}
					}
					else
					{
						k = 1;
						while (ft_isdigit(assembly[*i][k]))
							k++;
						if (assembly[*i][k] && (assembly[*i][k] != SEPARATOR_CHAR || assembly[*i][k + 1]))
							return (-8);
						k = ft_atoi(assembly[*i]);
					}
					write_byteswapped(&code[pc], &k, 2);
					pc += 2;
				}
				else
					return (-9);
				arg++;
				k = ft_strlen(assembly[*i]);
				if (arg < g_op_tab[j].num_args && assembly[*i][k - 1] != SEPARATOR_CHAR)
					return (-10);
				else if (arg >= g_op_tab[j].num_args && assembly[*i][k - 1] == SEPARATOR_CHAR)
					return (-11);
			}
			if (arg < g_op_tab[j].num_args)
				return (-12);
			break ;
		}
	if (!g_op_tab[j].mnemonic)
		return (-13);
	if (program)
		ft_memcpy(&program->code[program->header.prog_size], code, pc);
	return (pc);
}

t_list		*init_labels(char **assembly)
{
	size_t	i;
	size_t	pc;
	int		error;
	t_list	*label;
	t_list	*labels;

	i = 0;
	pc = 0;
	labels = 0;
	while (assembly[i])
	{
		error = assemble(assembly, &i, 0, labels);
		if (error < 0)
		{
			ft_printf("Assembly error! Error code: %d; |%s|\n", error, assembly[i]);
			ft_lstdel(&labels, (void (*)(void *, size_t))free);
			return (0);
		}
		if (!error)
		{
			if (!(label = ft_lstnew(assembly[i], ft_strlen(assembly[i]))))
			{
				ft_lstdel(&labels, (void (*)(void *, size_t))free);
				return ((t_list *)(long)ft_puterror("Failed to allocate memory!\n", 0));
			}
			i++;
			label->content_size = pc;
			ft_lstadd(&labels, label);
		}
		pc += (unsigned int)error;
	}
	return (labels);
}

t_program	*the_assemble_everything_function(char *source)
{
	t_program	*program;
	char		**assembly;
	t_list		*labels;
	size_t		i;
	int			error;

	if (!(program = ft_memalloc(sizeof(t_program) + CHAMP_MAX_SIZE)))
		return ((t_program *)(long)ft_puterror("Failed to allocate memory!\n", 0));
	program->header.magic = ((COREWAR_EXEC_MAGIC & 0xFF) << 24) | ((COREWAR_EXEC_MAGIC & 0xFF00) << 8) |
							((COREWAR_EXEC_MAGIC & 0xFF0000) >> 8) | ((COREWAR_EXEC_MAGIC & 0xFF000000) >> 24);
	assembly = parse_source(source, program);
	if (!(labels = init_labels(assembly)))
	{
		free(program);
		return (0);
	}
	i = 0;
	while (assembly[i])
	{
		error = assemble(assembly, &i, program, labels);
		if (error < 0)
		{
			ft_printf("Assembly error! Error code: %d\n", error);
			ft_lstdel(&labels, (void (*)(void *, size_t))free);
			free(program);
			return (0);
		}
		if (!error)
			i++;
		program->header.prog_size += (unsigned int)error;
	}
	return (program);
}
