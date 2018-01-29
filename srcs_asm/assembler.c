/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:09:54 by apuel             #+#    #+#             */
/*   Updated: 2018/01/25 22:36:27 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

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
