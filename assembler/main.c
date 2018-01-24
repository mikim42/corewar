/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:55:08 by apuel             #+#    #+#             */
/*   Updated: 2018/01/23 13:55:17 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "op_ext.h"

void		write_byteswapped(void *dst, void *src, size_t n);
t_program	*the_assemble_everything_function(char *source);

size_t	ft_getfilesize(char *path)
{
	unsigned char	buffer[4096];
	size_t			size;
	int				fd;
	int				br;

	fd = open(path, O_RDONLY, 0);
	size = 0;
	if (fd >= 0)
	{
		while ((br = read(fd, buffer, 4096)) > 0)
			size += br;
		close(fd);
	}
	return (size);
}

unsigned char	*ft_readfile(char *path, size_t *size)
{
	unsigned char	*buffer;
	size_t			i;
	int				fd;
	int				br;

	if (size)
		*size = ft_getfilesize(path);
	if (size && *size)
		buffer = malloc(*size);
	else
		return ((unsigned char *)0);
	if (buffer)
	{
		fd = open(path, O_RDONLY, 0);
		i = 0;
		if (fd >= 0)
		{
			while ((br = read(fd, &buffer[i], 4096)) > 0)
				i += br;
			close(fd);
			buffer[i] = '\0';
		}
	}
	return (buffer);
}

int	main(int argc, char **argv)
{
	char		*source;
	size_t		size;
	t_program	*program;
	int			i;
	int			fd;

	i = 0;
	while (++i < argc)
	{
		ft_printf("Assembling %s...\n", argv[i]);
		source = (char *)ft_readfile(argv[i], &size);
		if ((program = the_assemble_everything_function(source)))
		{
			fd = open(ft_strjoin(argv[i], ".cor"), O_CREAT | O_TRUNC | O_WRONLY, 0666);
			size = program->header.prog_size;
			write_byteswapped(&program->header.prog_size, &size, 4);
			write(fd, program, sizeof(t_program) + size);
			close(fd);
			ft_printf("Done!\n", argv[i]);
		}
	}
	return (0);
}
