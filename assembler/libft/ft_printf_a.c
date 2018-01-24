/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 20:10:26 by ashih             #+#    #+#             */
/*   Updated: 2017/12/15 21:31:22 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_a(va_list *args, int *flags, int *chars_printed)
{
	char	result[L_DBL_DEC_STR_MAX_LEN];

	if (flags[i_big_l] == 1)
		ft_printf_l_dbl_to_hex_str(va_arg(*args, long double),
				result, flags, 0);
	else
		ft_printf_l_dbl_to_hex_str(va_arg(*args, double), result, flags, 0);
	flags[i_dot] = 0;
	ft_printf_x_format(result, flags, chars_printed, "");
}

void		ft_printf_big_a(va_list *args, int *flags, int *chars_printed)
{
	char	result[L_DBL_DEC_STR_MAX_LEN];

	if (flags[i_big_l] == 1)
		ft_printf_l_dbl_to_hex_str(va_arg(*args, long double),
				result, flags, 1);
	else
		ft_printf_l_dbl_to_hex_str(va_arg(*args, double), result, flags, 1);
	flags[i_dot] = 0;
	ft_printf_x_format(result, flags, chars_printed, "");
}
