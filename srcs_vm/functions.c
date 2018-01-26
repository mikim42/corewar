/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:53:27 by ashih             #+#    #+#             */
/*   Updated: 2018/01/25 22:49:22 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int		count_bytes(unsigned char arg_code, int short_dir)
{
	if (arg_code == 0)
		return (0);
	else if (arg_code == REG_CODE)
		return (1);
	else if (arg_code == IND_CODE)
		return (2);
	else if (arg_code == DIR_CODE && short_dir == 1)
		return (2);
	else if (arg_code == DIR_CODE && short_dir == 0)
		return (4);
	else
		return (-1);
}

int			is_valid_reg(unsigned char reg_num)
{
	return (0 <= reg_num && reg_num < REG_NUMBER);
}


void		do_live(t_process *process, t_master *m)
{
	unsigned int	arg1;

	process->lives++;
	arg1 = (m->core[(process->pc + 1) % MEM_SIZE].value << 24) |
		(m->core[(process->pc + 2) % MEM_SIZE].value << 16) |
		(m->core[(process->pc + 3) % MEM_SIZE].value << 8) |
		(m->core[(process->pc + 4) % MEM_SIZE].value << 0);
	if (arg1 == m->player[0].id)
		m->player[0].lives++;
	else if (arg1 == m->player[1].id)
		m->player[1].lives++;
	else if (arg1 == m->player[2].id)
		m->player[2].lives++;
	else if (arg1 == m->player[3].id)
		m->player[3].lives++;
	process->pc = (process->pc + 5) % MEM_SIZE;
}



void		do_ld(t_process *process, t_master *m)
{
	unsigned char	arg1;
	unsigned char	arg2;
	unsigned int	reg_num;
	unsigned int	temp_pc;

	arg1 = (m->core[(process->pc + 1) % MEM_SIZE].value >> 6) & 0x3;
	arg2 = (m->core[(process->pc + 1) % MEM_SIZE].value >> 4) & 0x3;
	reg_num = m->core[(process->pc + 2 + count_bytes(arg1, 0))
		% MEM_SIZE].value - 1;

	if ((arg1 == DIR_CODE || arg1 == IND_CODE) &&
		arg2 == REG_CODE && is_valid_reg(reg_num))
	{
		/*
		if (arg1 == DIR_CODE)
		{
			process->reg[reg_num] =
				((int)m->core[(process->pc + 2) % MEM_SIZE].value << 24) |
				((int)m->core[(process->pc + 3) % MEM_SIZE].value << 16) |
				((int)m->core[(process->pc + 4) % MEM_SIZE].value << 8) |
				((int)m->core[(process->pc + 5) % MEM_SIZE].value << 0);
		}
		else if (arg1 == IND_CODE)
		{
			temp_pc = process->pc;
			temp_pc +=
				(((int)m->core[(process->pc + 2) % MEM_SIZE].value << 8) |
				((int)m->core[(process->pc + 3) % MEM_SIZE].value)) % IDX_MOD;
			temp_pc %= MEM_SIZE;
		}
		*/
		temp_pc = (process->pc + 2) % MEM_SIZE;
		if (arg1 == IND_CODE)
		{
			temp_pc = process->pc;
			temp_pc +=
				(((int)m->core[(process->pc + 2) % MEM_SIZE].value << 8) |
				((int)m->core[(process->pc + 3) % MEM_SIZE].value)) % IDX_MOD;
			temp_pc %= MEM_SIZE;
		}

		process->reg[reg_num] =
			((int)m->core[(temp_pc + 0) % MEM_SIZE].value << 24) |
			((int)m->core[(temp_pc + 1) % MEM_SIZE].value << 16) |
			((int)m->core[(temp_pc + 2) % MEM_SIZE].value << 8) |
			((int)m->core[(temp_pc + 3) % MEM_SIZE].value << 0);
		process->carry = (process->reg[reg_num] == 0) ? 1 : 0;
	}
	// move the process pc no matter if args are valid or not
	process->pc = (process->pc + 2 + count_bytes(arg1, 0) +
		count_bytes(arg2, 0)) % MEM_SIZE;

	
}

void		do_st(t_process *process, t_master *m)
{
	unsigned char	arg1;
	unsigned char	arg2;
	unsigned int	arg1_reg_num;
	unsigned int	arg2_reg_num;
	unsigned int	temp_pc;

	arg1 = (m->core[(process->pc + 1) % MEM_SIZE].value >> 6) & 0x3;
	arg2 = (m->core[(process->pc + 1) % MEM_SIZE].value >> 4) & 0x3;
	arg1_reg_num = m->core[(process->pc + 2) % MEM_SIZE].value - 1;

	if (arg1 == REG_CODE && is_valid_reg(arg1_reg_num) &&
		(arg2 == IND_CODE || (arg2 == REG_CODE &&
		is_valid_reg(arg2_reg_num = m->core[(process->pc + 2 +
		count_bytes(arg1, 0)) % MEM_SIZE].value - 1))))
	{
		if (arg2 == REG_CODE)
			process->reg[arg2_reg_num] = process->reg[arg1_reg_num];
		else
		{
			temp_pc = process->pc;
			temp_pc += (((int)m->core[(process->pc + count_bytes(arg1, 0) + 2)
				% MEM_SIZE].value << 8) |
				((int)m->core[(process->pc + count_bytes(arg1, 0) + 3)
				% MEM_SIZE].value)) % IDX_MOD;
			m->core[(temp_pc + 0) % MEM_SIZE].value =
				(process->reg[arg1_reg_num] >> 24) & 0xFF;
			m->core[(temp_pc + 1) % MEM_SIZE].value =
				(process->reg[arg1_reg_num] >> 16) & 0xFF;
			m->core[(temp_pc + 2) % MEM_SIZE].value =
				(process->reg[arg1_reg_num] >> 8) & 0xFF;
			m->core[(temp_pc + 3) % MEM_SIZE].value =
				(process->reg[arg1_reg_num] >> 0) & 0xFF;
		}
		process->carry = (process->reg[arg1_reg_num] == 0) ? 1 : 0;
	}
	// move the process pc no matter if args are valid or not
	process->pc = (process->pc + 2 + count_bytes(arg1, 0) +
		count_bytes(arg2, 0)) % MEM_SIZE;
}

void		do_add(t_process *process, t_master *m);
void		do_sub(t_process *process, t_master *m);
void		do_and(t_process *process, t_master *m);
void		do_or(t_process *process, t_master *m);
void		do_xor(t_process *process, t_master *m);

void		do_zjmp(t_process *process, t_master *m)
{
	short	arg1;

	if (process->carry == 0)
	{
		process->pc = (process->pc + 3) % MEM_SIZE;
		return ;
	}
	arg1 = ((short)m->core[(process->pc + 1) % MEM_SIZE].value << 8) |
		((short)m->core[(process->pc + 2) % MEM_SIZE].value << 0);
	process->pc += arg1 % IDX_MOD;
	process->pc %= MEM_SIZE;
}

void		do_ldi(t_process *process, t_master *m);

void		do_sti(t_process *process, t_master *m);

void		do_fork(t_process *process, t_master *m);
void		do_lld(t_process *process, t_master *m);
void		do_lldi(t_process *process, t_master *m);
void		do_lfork(t_process *process, t_master *m);

void		append_afflog(unsigned int reg_num, t_process *process, t_master *m)
{
	char	*afflog;
	int		i;
	
	afflog = m->player[process->owner - 1].afflog;
	i = 0;
	while (afflog[i])
		i++;
	afflog[i++] = process->reg[reg_num] % 256;
	afflog[i] = '\0';
}


void		do_aff(t_process *process, t_master *m)
{
	unsigned char	arg1;
	unsigned int	reg_num;

	arg1 = (m->core[(process->pc + 1) % MEM_SIZE].value >> 6) & 0x3;
	reg_num = m->core[(process->pc + 2) % MEM_SIZE].value - 1;

	if (arg1 == REG_CODE && is_valid_reg(reg_num))
	{
		append_afflog(reg_num, process, m);
	}
	// move the process pc no matter if args are valid or not
	process->pc = (process->pc + 2 + count_bytes(arg1, 0)) % MEM_SIZE;
}


void		do_fork(t_process *process, t_master *m);

// do I really need this LOL
void		do_nop(t_process *process, t_master *m)
{
	(void)process;
	(void)m;
}
