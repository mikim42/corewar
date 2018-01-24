/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:06:08 by ashih             #+#    #+#             */
/*   Updated: 2017/12/17 03:29:42 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_d(va_list *args, int *flags, int *chars_printed)
{
	char	result[DEC_STR_MAX_LEN];
	char	prefix[2];
	char	*expr;

	if (flags[i_l] || flags[i_ll] || flags[i_j] || flags[i_z])
		ft_printf_num_to_str(va_arg(*args, long), result, flags);
	else if (flags[i_h])
		ft_printf_num_to_str((short)va_arg(*args, int), result, flags);
	else if (flags[i_hh])
		ft_printf_num_to_str((char)va_arg(*args, int), result, flags);
	else
		ft_printf_num_to_str(va_arg(*args, int), result, flags);
	prefix[0] = (*result == '+' || *result == '-' || *result == ' ') ?
		*result : '\0';
	prefix[1] = '\0';
	expr = prefix[0] == '\0' ? result : result + 1;
	ft_printf_d_format(expr, flags, chars_printed, prefix);
}

void		ft_printf_big_d(va_list *args, int *flags, int *chars_printed)
{
	char	result[DEC_STR_MAX_LEN];
	char	prefix[2];
	char	*expr;

	ft_printf_num_to_str(va_arg(*args, long), result, flags);
	prefix[0] = (*result == '+' || *result == '-' || *result == ' ') ?
		*result : '\0';
	prefix[1] = '\0';
	expr = prefix[0] == '\0' ? result : result + 1;
	ft_printf_d_format(expr, flags, chars_printed, prefix);
}
