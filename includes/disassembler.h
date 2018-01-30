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

# define PROGRAM_HEADER \
"# ***************************************************************************"\
"* #\n"\
"#                                                                            "\
"  #\n"\
"#                                                         :::      ::::::::  "\
"  #\n"\
"#    %-40.40s           :+:      :+:    :+:    #\n"\
"#                                                     +:+ +:+         +:+    "\
"  #\n"\
"#    By: CoreWar Disassembler                       +#+  +:+       +#+       "\
"  #\n"\
"#                                                 +#+#+#+#+#+   +#+          "\
"  #\n"\
"#    Authors: apuel, ashih, mikim                      #+#    #+#            "\
"  #\n"\
"#    https://github.com/mikim42/corewar               ###   ########.fr      "\
"  #\n"\
"#                                                                            "\
"  #\n"\
"# ***************************************************************************"\
"* #\n\n"

size_t			count_bytes(unsigned char arg_code, int short_dir);
unsigned char	get_type(unsigned char op, unsigned char *code, unsigned int i);
int				validate_args(unsigned char *code);
size_t			instruction_length(unsigned char *code);

void			write_byteswapped(void *dst, void *src, size_t n);
void			disassemble(t_program *program);

#endif
