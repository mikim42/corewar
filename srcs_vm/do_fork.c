/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 03:10:40 by ashih             #+#    #+#             */
/*   Updated: 2018/01/27 03:10:49 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		do_fork(t_process *process, t_master *m)
{
	t_process	new_process;

	ft_memcpy(&new_process, process, sizeof(t_process));
	new_process.pc += cached_short(process, 1) % IDX_MOD;
	new_process.pc %= MEM_SIZE;
	new_process.cycles = 0;
	ft_bzero(new_process.icache, 0x10);
	process->player->process_count++;
	ft_lstadd(&(m->process_list),
		ft_lstnew(&new_process, sizeof(t_process)));
	process->pc = (process->pc + 3) % MEM_SIZE;
}
