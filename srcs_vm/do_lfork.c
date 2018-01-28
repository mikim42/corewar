/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 03:11:51 by ashih             #+#    #+#             */
/*   Updated: 2018/01/27 03:12:02 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		do_lfork(t_process *process, t_master *m)
{
	t_process	new_process;

	ft_memcpy(&new_process, process, sizeof(t_process));
	new_process.pc += read_short(m, process->pc + 1);
	new_process.pc %= MEM_SIZE;
	new_process.cycles = 0;
	new_process.opcode = 0;
	process->player->process_count++;
	ft_lstadd(&(m->process_list),
		ft_lstnew(&new_process, sizeof(t_process)));
	process->pc = (process->pc + 3) % MEM_SIZE;
}
