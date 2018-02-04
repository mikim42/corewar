/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 16:33:22 by ashih             #+#    #+#             */
/*   Updated: 2018/02/03 16:37:36 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			build_last_cycle(t_master *m)
{
	m->current_cycle++;
	run_processes(m);
	reap_processes(m);
	ft_lstdel(&(m->process_list), del_process);
	if (m->winner == 0)
		m->winner = &(m->player[m->player_count - 1]);
	if (m->v_flag == 0)
		return ;
	announce_winner(m);
}

void			announce_winner(t_master *m)
{
	static char	*prefix[8] = {
		"sleep 1 && say -v Victoria -r 240 'Player 1. ",
		"sleep 1 && say -v Victoria -r 240 'Player 2. ",
		"sleep 1 && say -v Victoria -r 240 'Player 3. ",
		"sleep 1 && say -v Victoria -r 240 'Player 4. ",
		"sleep 1 && say -v Victoria -r 240 'Player 1. Burger ",
		"sleep 1 && say -v Victoria -r 240 'Player 2. Chicken ",
		"sleep 1 && say -v Victoria -r 240 'Player 3. Robot ",
		"sleep 1 && say -v Victoria -r 240 'Player 4. Virus "};
	int			i;
	char		*full_str;
	char		*temp;

	i = -(m->winner->id) - 1;
	if (m->e_flag)
		i += 4;
	temp = ft_strjoin(prefix[i], m->winner->name);
	full_str = ft_strjoin(temp, ". won' &");
	ft_strdel(&temp);
	system(full_str);
	ft_strdel(&full_str);
}
