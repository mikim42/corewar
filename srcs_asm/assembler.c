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

int			is_valid_label(char *label)
{
	while (*label && *(label + 1))
	{
		if (!ft_strchr(LABEL_CHARS, *label))
			return (0);
		label++;
	}
	return (*label == LABEL_CHAR);
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
