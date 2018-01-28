/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 03:12:08 by ashih             #+#    #+#             */
/*   Updated: 2018/01/27 03:12:21 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		do_aff(t_process *process, t_master *m)
{
	if (validate_args(process, m))
		append_afflog(read_reg_exact(process, m, 0), process);
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}

void		append_afflog(unsigned int reg_num, t_process *process)
{
	char	*afflog;
	int		i;

	afflog = process->player->afflog;
	i = 0;
	while (afflog[i])
		i++;
	if (i != AFFLOG_SIZE)
	{
		afflog[i] = process->reg[reg_num] % 256;
		return ;
	}
	i = -1;
	while (++i < AFFLOG_SIZE - 1)
		afflog[i] = afflog[i + 1];
	afflog[i] = process->reg[reg_num] % 256;
}
