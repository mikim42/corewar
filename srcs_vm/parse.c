/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 23:49:33 by ashih             #+#    #+#             */
/*   Updated: 2018/01/30 17:39:55 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		parse_args(int argc, char **argv, t_master *m)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (parse_arg(argc, &i, argv, m))
			return (1);
	}
	if (m->open_spot == 0)
		return (ft_puterror(ERROR_FEW_PLAYERS, 1));
	shuffle_players(m);
	init_progs(m);
	return (0);
}

/*
** int parse_arg(int argc, int *i, char **argv, t_master *m);
**
** First try to parse an arg as a flag, which might involve more args;
** If failed, try to parse as a champion program.
*/

int		parse_arg(int argc, int *i, char **argv, t_master *m)
{
	if (ft_strequ(argv[*i], "-v"))
		return (!(m->v_flag = 1));
	if (ft_strequ(argv[*i], "-e"))
		return (!(m->e_flag = 1));
	if (ft_strequ(argv[*i], "-dump"))
	{
		return ((++(*i) < argc && !ft_atoi_check(argv[*i],
			&(m->d_flag))) ? 0 : ft_puterror(ERROR_USAGE, 1));
	}
	if (ft_strequ(argv[*i], "-n"))
	{
		if (++(*i) >= argc || ft_atoi_check(argv[*i],
			&(m->n_flag)))
			return (ft_puterror(ERROR_USAGE, 1));
		if (++(*i) >= argc)
			return (ft_puterror(ERROR_USAGE, 1));
		return (read_player(argv[*i], m));
	}
	return (read_player(argv[*i], m));
}

int		read_player(char *argv, t_master *m)
{
	if (m->open_spot == 4)
		return (ft_puterror(ERROR_MANY_PLAYERS, 1));
	if (m->n_flag != 0)
	{
		m->player[m->open_spot].n_flag_pos = m->n_flag;
		m->n_flag = 0;
	}
	m->player[m->open_spot].id = P1_ID - m->player_count++;
	m->player[m->open_spot].master = m;
	if (read_file(argv, m->player + m->open_spot))
		return (1);
	m->open_spot++;
	return (0);
}

int		read_file(char *filename, t_player *p)
{
	int	fd;

	if (fail_cor_ender(filename))
	{
		ft_puterror(ERROR_COR_TYPE, 1);
		ft_printf("{poop} Invalid file: %s\n", filename);
		return (1);
	}
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_puterror(ERROR_OPEN_FILE, 1);
		ft_printf("{poop} Invalid file: %s\n", filename);
		return (1);
	}
	if (read_everything(fd, p))
	{
		close(fd);
		ft_printf("{poop} Invalid file: %s\n", filename);
		return (1);
	}
	if (close(fd) == -1)
		return (ft_puterror(ERROR_CLOSE_FILE, 1));
	return (0);
}

/*
** int read_everything(int fd, t_player *p);
**
** (1) Read 4 bytes and check it matches the magic header.
** (2) Read 128 bytes of program name, followed by 4 zeroed bytes.
** (3) Read 4 bytes which indicate size of program instructions.
** (4) Read 2048 bytes of program comment, followed by 4 zeroed bytes.
** (5) Read the program instructions of exactly prog_size bytes given earlier.
*/

int		read_everything(int fd, t_player *p)
{
	unsigned char	buf[4];

	if (!(read(fd, buf, 4) == 4 && ft_memcmp(buf, "\x00\xea\x83\xf3", 4) == 0))
		return (ft_puterror(ERROR_HEADER, 1));
	read(fd, p->name, PROG_NAME_LENGTH);
	if (!(read(fd, buf, 4) == 4 && ft_memcmp(buf, "\0\0\0\0", 4) == 0))
		return (ft_puterror(ERROR_FORMAT, 1));
	if (!(read(fd, buf, 4) == 4))
		return (ft_puterror(ERROR_FORMAT, 1));
	p->prog_size = (unsigned int)buf[3] | ((unsigned int)buf[2] << 8) |
		((unsigned int)buf[1] << 16) | ((unsigned int)buf[0] << 24);
	if (p->prog_size > CHAMP_MAX_SIZE)
		return (ft_puterror(ERROR_CHAMP_SIZE, 1));
	if (p->prog_size == 0)
		return (ft_puterror(ERROR_EMPTY_SIZE, 1));
	read(fd, p->comment, COMMENT_LENGTH);
	if (!(read(fd, buf, 4) == 4 && ft_memcmp(buf, "\0\0\0\0", 4) == 0))
		return (ft_puterror(ERROR_FORMAT, 1));
	p->prog = malloc(sizeof(unsigned char) * p->prog_size);
	if (!(read(fd, p->prog, p->prog_size) == p->prog_size &&
		read(fd, buf, 4) == 0))
		return (ft_puterror(ERROR_FORMAT, 1));
	return (0);
}
