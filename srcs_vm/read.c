/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 22:24:31 by ashih             #+#    #+#             */
/*   Updated: 2018/01/25 22:29:08 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				read_players(int argc, char **argv, t_master *m)
{
	int			i;
	i = 0;
	while (++i < argc)
	{
		m->player[i - 1].id = P1_ID - m->player_count++;
		if (read_file(argv[i], m->player + i - 1))
			return (1);
	}
	init_progs(m);
	return (0);
}

int			read_file(char *filename, t_player *p)
{
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (ft_puterror(ERROR_OPEN_FILE, 1));
	if (read_everything(fd, p))
		return (1);
	if (close(fd) == -1)
		return (ft_puterror(ERROR_CLOSE_FILE, 1));
	return (0);
}

int					read_everything(int fd, t_player *p)
{
	unsigned char	buf[4];

	// check header
	if (!(read(fd, buf, 4) == 4 && ft_memcmp(buf, "\x00\xea\x83\xf3", 4) == 0))
		return (1);

	// read player name, no error checking
	read(fd, p->name, PROG_NAME_LENGTH);
//	p->name[PROG_NAME_LENGTH] = '\0';

	// check 4 bytes of zero padding
	if (!(read(fd, buf, 4) == 4 && ft_memcmp(buf, "\0\0\0\0", 4) == 0))
		return (1);

	// check program size given in next 4 bytes
	if (!(read(fd, buf, 4) == 4))
		return (1);
	p->prog_size = (unsigned int)buf[3] | ((unsigned int)buf[2] << 8) |
		((unsigned int)buf[1] << 16) | ((unsigned int)buf[0] << 24);
	if (p->prog_size > CHAMP_MAX_SIZE)
		return (1);

	// read player comment, no error checking
	read(fd, p->comment, COMMENT_LENGTH);
//	p->comment[COMMENT_LENGTH] = '\0';

	// check 4 bytes of zero padding
	if (!(read(fd, buf, 4) == 4 && ft_memcmp(buf, "\0\0\0\0", 4) == 0))
		return (1);

	// read the program up to the given size
	p->prog = malloc(sizeof(unsigned char) * p->prog_size);
	if (!(read(fd, p->prog, p->prog_size) == p->prog_size &&
		read(fd, buf, 4) == 0))
		return (1);
		
	return (0);
}

void		init_progs(t_master *m)
{
	int		i;

	i = -1;
	while (++i < m->player_count)
		init_prog(i, m);
}

void		init_prog(int i, t_master *m)
{
	t_process		*first;
	unsigned int	j;

	// initialize 1 process
	first = ft_memalloc(sizeof(t_process));
	first->id = ++(m->player[i].process_count);
	first->owner = i + 1;
	first->reg[0] = m->player[i].id;
	ft_lstadd(&(m->player[i].process_list),
		ft_lst_new_ref(first, sizeof(t_process)));

	// copy prog to core
	first->pc = MEM_SIZE / (unsigned int)m->player_count * i;
	j = 0;
	while (j < m->player[i].prog_size)
	{
		m->core[(first->pc + j) % MEM_SIZE].value = m->player[i].prog[j];
		m->core[(first->pc + j) % MEM_SIZE].owner = i + 1;
		j++;
	}
}
