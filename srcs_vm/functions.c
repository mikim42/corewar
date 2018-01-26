/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:53:27 by ashih             #+#    #+#             */
/*   Updated: 2018/01/25 16:14:41 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		do_live(t_process *process, t_master *m)
{
	unsigned int	arg1;

	process->lives++;
	arg1 = m->core[(process->pc + 1) % MEM_SIZE].value |
		(m->core[(process->pc + 2) % MEM_SIZE].value) << 16 |
		(m->core[(process->pc + 3) % MEM_SIZE].value) << 32 |
		(m->core[(process->pc + 4) % MEM_SIZE].value) << 48;
	if (arg1 == m->player[0].id)
		m->player[0].lives++;
	else if (arg1 == m->player[1].id)
		m->player[1].lives++;
	else if (arg1 == m->player[2].id)
		m->player[2].lives++;
	else if (arg1 == m->player[3].id)
		m->player[3].lives++;
}

void		do_ld(t_process *process, t_master *m);
void		do_st(t_process *process, t_master *m);
void		do_add(t_process *process, t_master *m);
void		do_sub(t_process *process, t_master *m);
void		do_and(t_process *process, t_master *m);
void		do_or(t_process *process, t_master *m);
void		do_xor(t_process *process, t_master *m);

void		do_zjmp(t_process *process, t_master *m)
{
	int		arg1;

	if (process->carry_flag == 0)
		return ;
	arg1 = m->core[(process->pc + 1) % MEM_SIZE].value |
		(m->core[(process->pc + 2) % MEM_SIZE].value) << 16;
	process->pc = (process->pc + (unsigned int)(arg1 + MEM_SIZE)) % MEM_SIZE;
}

void		do_ldi(t_process *process, t_master *m);
void		do_sti(t_process *process, t_master *m);
void		do_fork(t_process *process, t_master *m);
void		do_lld(t_process *process, t_master *m);
void		do_lldi(t_process *process, t_master *m);
void		do_lfork(t_process *process, t_master *m);
void		do_aff(t_process *process, t_master *m);
void		do_fork(t_process *process, t_master *m);
