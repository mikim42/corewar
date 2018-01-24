/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:09:54 by apuel             #+#    #+#             */
/*   Updated: 2018/01/23 14:09:57 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

#include "libft.h"
#include "op_ext.h"

void		write_byteswapped(void *dst, void *src, size_t n);
t_program	*the_assemble_everything_function(char *source);
long		throw_error(char *string, long result);
long		throw_verbose_error(char *format, long f0, long f1, long f2);

#endif