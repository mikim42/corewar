/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 22:49:54 by ashih             #+#    #+#             */
/*   Updated: 2018/01/28 22:50:47 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			reap_processes(t_master *m)
{
	int			i;

	ft_lst_cond_remove(&(m->process_list), process_should_die,
		del_process);
	i = -1;
	while (++i < m->player_count)
	{
		m->player[i].last_lives = m->player[i].lives;
		m->player[i].lives = 0;
	}
}

int				process_should_die(void *process, size_t size)
{
	int			should_die;

	(void)size;
	should_die = ((t_process *)process)->lives == 0;
	((t_process *)process)->lives = 0;
	return (should_die);
}

void			del_process(void *process, size_t size)
{
	t_master	*m;

	(void)size;
	((t_process *)process)->player->process_count--;
	m = ((t_process *)process)->player->master;
	m->core[((t_process *)process)->pc].death = m->current_cycle + DEATH_LEN;
	m->core[((t_process *)process)->pc].dier =
		-(((t_process *)process)->player->id) - 1;
	ft_memdel(&process);
}
