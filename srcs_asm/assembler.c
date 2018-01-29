/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:09:54 by apuel             #+#    #+#             */
/*   Updated: 2018/01/28 16:38:02 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

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

void		the_assemble_part_two(char **assembly, t_program **program)
{
	t_list	*labels;
	int		error;
	size_t	i;

	i = 0;
	*program = init_program(assembly, *program, &labels, 0);
	if ((*program)->header.magic)
		while (*program && assembly[i])
		{
			error = assemble(assembly, &i, *program, labels);
			if (error >= 0)
			{
				(!error) ? i++ : 0;
				(*program)->header.prog_size += error;
			}
			else
				ft_memdel((void **)program);
		}
	else
		ft_memdel((void **)program);
	ft_lstdel(&labels, (void (*)(void *, size_t))free);
	i = 0;
	while (assembly[i])
		free(assembly[i++]);
	free(assembly);
}

t_program	*the_assemble_everything_function(char *source)
{
	t_program	*program;
	char		**assembly;

	if ((program = ft_memalloc(sizeof(t_program))))
	{
		if ((assembly = parse_source(source, program)))
			the_assemble_part_two(assembly, &program);
		else
			ft_memdel((void **)&program);
	}
	else
		throw_error(ALLOC_FAIL, 0);
	return (program);
}
