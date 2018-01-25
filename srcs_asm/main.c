/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:55:08 by apuel             #+#    #+#             */
/*   Updated: 2018/01/25 09:30:07 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

long	throw_error(char *string, long result)
{
	ft_printf("[!] %s\n", string);
	return (result);
}

long	throw_verbose_error(char *format, long f0, long f1, long f2)
{
	ft_printf("[!] ");
	ft_printf(format, f0, f1, f2);
	ft_printf("\n");
	return (-1);
}

char	*ft_readfile(char *path)
{
	char	*buffer;
	size_t	size;
	int		fd;

	if ((fd = open(path, O_RDONLY, 0)) < 0)
		return (NULL);
	size = lseek(fd, 0, SEEK_END);
	if ((size < 1) || !(buffer = ft_memalloc(size + 1)))
		return (NULL);
	lseek(fd, 0, SEEK_SET);
	read(fd, buffer, size);
	close(fd);
	return (buffer);
}

void	create_binary(t_program *program, char *name, size_t size)
{
	char	*tmp;
	int		fd;

	if ((tmp = ft_strjoin(name, "or")))
	{
		tmp[size - 1] = 'c';
		if ((fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0666)) >= 0)
		{
			size = program->header.prog_size;
			write_byteswapped(&program->header.prog_size, &size, 4);
			write(fd, program, sizeof(t_program) + size);
			close(fd);
		}
		else
			ft_printf("[!] Failed to create file, '%s'!\n", tmp);
		free(tmp);
	}
	else
		throw_error("Failed to allocate memory!", 0);
	free(program);
}

int		main(int argc, char **argv)
{
	t_program	*program;
	char		*source;
	size_t		size;
	int			i;

	i = 0;
	while (++i < argc)
	{
		if (!(size = ft_strlen(argv[i])) || (argv[i][size - 1] != 's' &&
			argv[i][size - 1] != 'S') || argv[i][size - 2] != '.')
		{
			ft_printf("[!] '%s' has an invalid filetype!\n", argv[i]);
			continue ;
		}
		if ((source = ft_readfile(argv[i])))
		{
			if ((program = the_assemble_everything_function(source)))
				create_binary(program, argv[i], size);
			free(source);
		}
		else
			ft_printf("[!] Failed to read '%s'!\n", argv[i]);
	}
	return (0);
}
