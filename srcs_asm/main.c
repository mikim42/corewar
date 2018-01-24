/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:55:08 by apuel             #+#    #+#             */
/*   Updated: 2018/01/24 14:51:29 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "assembler.h"

long			throw_error(char *string, long result)
{
	ft_printf("[!] %s\n", string);
	return (result);
}

long			throw_verbose_error(char *format, long f0, long f1, long f2)
{
	ft_printf("[!] ");
	ft_printf(format, f0, f1, f2);
	ft_printf("\n");
	return (-1);
}

unsigned char	*ft_readfile(char *path, size_t *size)
{
	unsigned char	*buffer;
	int				fd;

	if ((fd = open(path, O_RDONLY, 0)) < 0)
		return (NULL);
	*size = lseek(fd, 0, SEEK_END);
	if ((*size < 1) || !(buffer = ft_memalloc(*size)))
		return (NULL);
	lseek(fd, 0, SEEK_SET);
	read(fd, buffer, *size);
	close(fd);
	return (buffer);
}

int				main(int argc, char **argv)
{
	char		*source;
	char		*deleteme;
	size_t		size;
	t_program	*program;
	int			i;
	int			fd;

	i = 0;
	while (++i < argc)
	{
		size = ft_strlen(argv[i]);
		if (!size || (argv[i][size - 1] != 's' &&
				argv[i][size - 1] != 'S') || argv[i][size - 2] != '.')
		{
			ft_printf("[!] %s has an invalid filetype!\n", argv[i]);
			continue ;
		}
		ft_printf("Assembling %s...\n", argv[i]);
		if ((source = (char *)ft_readfile(argv[i], &size)))
		{
			if ((program = the_assemble_everything_function(source)))
			{
				size = ft_strlen(argv[i]);
				if ((deleteme = ft_strjoin(argv[i], "or")))
				{
					deleteme[size - 1] = 'c';
					if ((fd = open(deleteme, O_CREAT | O_TRUNC | O_WRONLY, 0666)) >= 0)
					{
						size = program->header.prog_size;
						write_byteswapped(&program->header.prog_size, &size, 4);
						write(fd, program, sizeof(t_program) + size);
						close(fd);
						ft_printf("Done!\n", argv[i]);
					}
					else
						ft_printf("[!] Failed to create file, %s!\n", deleteme);
					free(deleteme);
				}
				else
					throw_error("Failed to allocate memory!", 0);
				free(program);
			}
			free(source);
		}
		else
			ft_printf("[!] Failed to read %s!\n", argv[i]);
	}
	return (0);
}
