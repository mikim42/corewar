/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 22:59:00 by apuel             #+#    #+#             */
/*   Updated: 2018/01/29 22:59:02 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

int			fail_cor_ender(char *filename)
{
	char	ender[5];
	int		i;

	if (ft_strlen(filename) < 4)
		return (1);
	ft_strcpy(ender, filename + ft_strlen(filename) - 4);
	i = 0;
	while (++i < 4)
		ender[i] = (char)ft_toupper(ender[i]);
	return (ft_strequ(".COR", ender) ? 0 : 1);
}

t_program	*read_program(char *path)
{
	t_program		*program;
	size_t			size;
	int				fd;
	unsigned int	magic;
	unsigned int	prog_size;

	if ((fd = open(path, O_RDONLY, 0)) < 0)
		return (NULL);
	size = lseek(fd, 0, SEEK_END);
	if (size < sizeof(t_program) || !(program = ft_memalloc(size + 1)))
		return (NULL);
	lseek(fd, 0, SEEK_SET);
	read(fd, program, size);
	close(fd);
	write_byteswapped(&magic, &(program->header.magic), 4);
	write_byteswapped(&prog_size, &(program->header.prog_size), 4);
	if (magic != COREWAR_EXEC_MAGIC || prog_size != size - sizeof(t_program))
		ft_memdel((void **)&program);
	else
	{
		program->header.prog_name[PROG_NAME_LENGTH] = '\0';
		program->header.comment[COMMENT_LENGTH] = '\0';
	}
	return (program);
}

int			main(int argc, char **argv)
{
	t_program	*program;
	int			i;

	i = 0;
	while (++i < argc)
	{
		if (fail_cor_ender(argv[i]))
		{
			ft_printf("[!] '%s' has an invalid filetype!\n", argv[i]);
			return (-1);
		}
		if ((program = read_program(argv[i])))
		{
			if (i > 1)
				ft_printf("\n");
			disassemble(program);
			free(program);
			continue ;
		}
		ft_printf("[!] Failed to read '%s'!\n", argv[i]);
		return (-1);
	}
	return (0);
}
