/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 03:04:40 by ashih             #+#    #+#             */
/*   Updated: 2018/01/27 03:04:52 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	do_st(t_process *process, t_master *m)
{
	unsigned char	type;
	unsigned int	offset;

	if (validate_args(process, m))
	{
		type = m->core[(process->pc + 1) % MEM_SIZE].value;
		type = (type >> 4) & 3;
		if (type == T_REG)
		{
			process->reg[read_reg_exact(process, m, 1)] =
													read_arg(process, m, 0);
		}
		else
		{
			offset = process->pc;
			offset += read_ind_exact(process, m, 1) % IDX_MOD;
			write_int(process, m, offset, read_arg(process, m, 0));
		}
	}
	process->pc = (process->pc + instruction_length(process, m)) % MEM_SIZE;
}
