/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 22:34:45 by mikim             #+#    #+#             */
/*   Updated: 2018/01/28 19:49:54 by apuel            ###   ########.fr       */
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
