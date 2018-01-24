/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 13:29:28 by ashih             #+#    #+#             */
/*   Updated: 2017/12/17 03:30:42 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_u(va_list *args, int *flags, int *chars_printed)
{
	char	result[DEC_STR_MAX_LEN];

	if (flags[i_l] || flags[i_ll] || flags[i_j] || flags[i_z])
		ft_printf_unum_to_dec_str(va_arg(*args, unsigned long), result, flags);
	else if (flags[i_h])
		ft_printf_unum_to_dec_str((unsigned short)va_arg(*args, unsigned int),
				result, flags);
	else if (flags[i_hh])
		ft_printf_unum_to_dec_str((unsigned char)va_arg(*args, unsigned int),
				result, flags);
	else
		ft_printf_unum_to_dec_str(va_arg(*args, unsigned int),
				result, flags);
	ft_printf_x_format(result, flags, chars_printed, "");
}

void		ft_printf_big_u(va_list *args, int *flags, int *chars_printed)
{
	char	result[DEC_STR_MAX_LEN];

	ft_printf_unum_to_dec_str(va_arg(*args, unsigned long), result, flags);
	ft_printf_x_format(result, flags, chars_printed, "");
}

void		ft_printf_unum_to_dec_str(unsigned long n, char *result, int *flags)
{
	int		i;

	i = 0;
	if (n == 0)
		result[i++] = '0';
	else
		while (n != 0)
		{
			result[i++] = n % 10 + '0';
			n = n / 10;
		}
	result[i] = '\0';
	ft_strrev(result);
	if (flags[i_apostrophe] == 1)
		ft_printf_apply_div(result);
}
