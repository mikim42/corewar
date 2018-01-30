/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 22:59:13 by apuel             #+#    #+#             */
/*   Updated: 2018/01/29 22:59:14 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASSEMBLER_H
# define DISASSEMBLER_H

# include "libft.h"
# include "op_ext.h"

# define PROGRAM_HEADER PHDR0
# define PHDR0 "# **************************************" PHDR1
# define PHDR1 "************************************** #\n" PHDR2
# define PHDR2 "#                                       " PHDR3
# define PHDR3 "                                       #\n" PHDR4
# define PHDR4 "#                                       " PHDR5
# define PHDR5 "                  :::      ::::::::    #\n" PHDR6
# define PHDR6 "#    %-40.40s           :+:      :+:    " PHDR7
# define PHDR7 ":+:    #\n" PHDR8
# define PHDR8 "#                                       " PHDR9
# define PHDR9 "              +:+ +:+         +:+      #\n" PHDR10
# define PHDR10 "#    By: CoreWar Disassembler           " PHDR11
# define PHDR11 "            +#+  +:+       +#+         #\n" PHDR12
# define PHDR12 "#                                       " PHDR13
# define PHDR13 "          +#+#+#+#+#+   +#+            #\n" PHDR14
# define PHDR14 "#    Authors: apuel, ashih, mikim       " PHDR15
# define PHDR15 "               #+#    #+#              #\n" PHDR16
# define PHDR16 "#    https://github.com/mikim42/corewar " PHDR17
# define PHDR17 "              ###   ########.fr        #\n" PHDR18
# define PHDR18 "#                                       " PHDR19
# define PHDR19 "                                       #\n" PHDR20
# define PHDR20 "# **************************************" PHDR21
# define PHDR21 "************************************** #\n\n"

size_t			count_bytes(unsigned char arg_code, int short_dir);
unsigned char	get_type(unsigned char op, unsigned char *code, unsigned int i);
int				validate_args(unsigned char *code);
size_t			instruction_length(unsigned char *code);

void			write_byteswapped(void *dst, void *src, size_t n);
void			disassemble(t_program *program);

#endif
