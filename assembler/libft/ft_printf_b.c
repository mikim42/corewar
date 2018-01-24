/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 01:04:46 by ashih             #+#    #+#             */
/*   Updated: 2017/12/16 19:15:58 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_b(va_list *args, int *flags, int *chars_printed)
{
	char	result[BIN_STR_MAX_LEN];
	char	*prefix;

	if (flags[i_hh])
		ft_printf_unum_to_bin_str((unsigned char)va_arg(*args, unsigned int),
				result, flags);
	else if (flags[i_h])
		ft_printf_unum_to_bin_str((unsigned short)va_arg(*args, unsigned int),
				result, flags);
	else if (flags[i_l] || flags[i_ll] || flags[i_j] || flags[i_z])
		ft_printf_unum_to_bin_str(va_arg(*args, unsigned long), result, flags);
	else
		ft_printf_unum_to_bin_str(va_arg(*args, unsigned int), result, flags);
	prefix = flags[i_num_sign] ? "0b" : "";
	ft_printf_x_format(result, flags, chars_printed, prefix);
}

void		ft_printf_big_b(va_list *args, int *flags, int *chars_printed)
{
	char	result[BIN_STR_MAX_LEN];
	char	*prefix;

	if (flags[i_hh])
		ft_printf_unum_to_bin_str((unsigned char)va_arg(*args, unsigned int),
				result, flags);
	else if (flags[i_h])
		ft_printf_unum_to_bin_str((unsigned short)va_arg(*args, unsigned int),
				result, flags);
	else if (flags[i_l] || flags[i_ll] || flags[i_j] || flags[i_z])
		ft_printf_unum_to_bin_str(va_arg(*args, unsigned long), result, flags);
	else
		ft_printf_unum_to_bin_str(va_arg(*args, unsigned int), result, flags);
	prefix = flags[i_num_sign] ? "0B" : "";
	ft_printf_x_format(result, flags, chars_printed, prefix);
}

void		ft_printf_unum_to_bin_str(unsigned long n, char *result, int *flags)
{
	int		i;

	i = 0;
	if (n == 0)
	{
		flags[i_num_sign] = 0;
		result[i++] = '0';
	}
	else
		while (n != 0)
		{
			result[i++] = n % 2 + '0';
			n = n / 2;
		}
	result[i] = '\0';
	ft_strrev(result);
}
