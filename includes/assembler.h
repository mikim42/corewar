/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:09:54 by apuel             #+#    #+#             */
/*   Updated: 2018/01/25 21:33:06 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

# include "libft.h"
# include "op_ext.h"

# define UNKNOWN_ARG "Unknown argument; '%s'!"
# define NOT_ENOUGH_ARG "Not enough arguments for %s!"
# define TOO_MANY_ARG "Too many arguments for %s!"

# define INVALID_ERR "Invalid '%s'!"
# define EOF_ERR "'%s' reaches EOF!"

# define INVALID_REG "Invalid type 'REG' for %s, argument %lu!"
# define BAD_REG "Bad 'REG' value; '%s'!" 

# define UNDEF_LABEL "Undefined label '%s'!"

# define INVALID_DIR "Invalid type 'DIRECT' for '%s', argument %lu!"
# define BAD_DIRECT "Bad 'DIRECT' value; '%s'!"

# define INVALID_INST "Invalid instruction '%s'!"
# define FILE_ABRUPT "File ended abruptly!"

typedef struct		s_asm_ctx
{
	unsigned char	code[0x10];
	size_t			pc;
	int				op;
	size_t			arg;
	t_list			*labels;
}					t_asm_ctx;

char				**split_syntax(const char *str);

void				write_byteswapped(void *dst, void *src, size_t n);
t_program			*the_assemble_everything_function(char *source);

long				throw_error(char *string, long result);
long				throw_verr(char *format, long f0, long f1, long f2);

#endif
