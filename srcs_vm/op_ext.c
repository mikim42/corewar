/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ext.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:09:54 by apuel             #+#    #+#             */
/*   Updated: 2018/01/25 15:21:59 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op			g_op_tab[17] =
{
	{"live", 1, {T_DIR, 0, 0}, 1, 10, "alive", 0, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG, 0}, 2, 5, "load", 1, 0, 0},
	{"st", 2, {T_REG, T_IND | T_REG, 0}, 3, 5, "store", 1, 0, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 0},
	{"zjmp", 1, {T_DIR, 0, 0}, 9, 20, "jump if zero", 0, 1, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, 0},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, 0},
	{"fork", 1, {T_DIR, 0, 0}, 12, 800, "fork", 0, 1, 0},
	{"lld", 2, {T_DIR | T_IND, T_REG, 0}, 13, 10, "long load", 1, 0, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 0},
	{"lfork", 1, {T_DIR, 0, 0}, 15, 1000, "long fork", 0, 1, 0},
	{"aff", 1, {T_REG, 0, 0}, 16, 2, "aff", 1, 0, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0}
};

t_op_length		g_op_length[59] =
{
	// live
	{0x01, 0, 5},
	
	// ld
	{0x02, 0x90, 7},
	{0x02, 0xd0, 5},

	// st
	{0x03, 0x50, 4},
	{0x03, 0x70, 5},

	// add
	{0x04, 0x54, 5},

	// sub
	{0x05, 0x54, 5},

	// and
	{0x06, 0x54, 5},
	{0x06, 0x74, 6},
	{0x06, 0x64, 8},
	
	{0x06, 0xd4, 6},
	{0x06, 0xf4, 7},
	{0x06, 0xe4, 9},

	{0x06, 0x94, 8},
	{0x06, 0xb4, 9},
	{0x06, 0xa4, 11},

	// or
	{0x07, 0x54, 5},
	{0x07, 0x74, 6},
	{0x07, 0x64, 8},
	
	{0x07, 0xd4, 6},
	{0x07, 0xf4, 7},
	{0x07, 0xe4, 9},

	{0x07, 0x94, 8},
	{0x07, 0xb4, 9},
	{0x07, 0xa4, 11},

	// xor
	{0x08, 0x54, 5},
	{0x08, 0x74, 6},
	{0x08, 0x64, 8},
	
	{0x08, 0xd4, 6},
	{0x08, 0xf4, 7},
	{0x08, 0xe4, 9},

	{0x08, 0x94, 8},
	{0x08, 0xb4, 9},
	{0x08, 0xa4, 11},

	// zjmp
	{0x09, 0, 3},
	
	// ldi
	{0x0a, 0x54, 5},
	{0x0a, 0x64, 6},
	
	{0x0a, 0xd4, 6},
	{0x0a, 0xe4, 7},

	{0x0a, 0x94, 6},
	{0x0a, 0xa4, 7},

	// sti
	{0x0b, 0x54, 5},
	{0x0b, 0x58, 6},
	
	{0x0b, 0x74, 6},
	{0x0b, 0x78, 7},
	
	{0x0b, 0x64, 6},
	{0x0b, 0x68, 7},

	// fork
	{0x0c, 0, 3},

	// lld
	{0x0d, 0x90, 7},
	{0x0d, 0xd0, 5},

	// lldi
	{0x0e, 0x54, 5},
	{0x0e, 0x64, 6},

	{0x0e, 0xd4, 6},
	{0x0e, 0xe4, 7},

	{0x0e, 0x94, 6},
	{0x0e, 0xa4, 7},
	
	// lfork
	{0x0f, 0, 3},
	
	// aff
	{0x10, 0x40, 3},

	// sentinel value
	{0, 0, 0}
};
