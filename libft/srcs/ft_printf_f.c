/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 02:25:42 by ashih             #+#    #+#             */
/*   Updated: 2017/12/26 00:45:08 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_printf_f(va_list *args, int *flags, int *chars_printed)
{
	char		result[L_DBL_DEC_STR_MAX_LEN];

	if (flags[i_big_l] == 1)
		ft_printf_l_dbl_to_str(va_arg(*args, long double), result, flags);
	else
		ft_printf_l_dbl_to_str(va_arg(*args, double), result, flags);
	flags[i_dot] = 0;
	ft_printf_x_format(result, flags, chars_printed, "");
}

void			ft_printf_l_dbl_to_str(long double d, char *result, int *flags)
{
	int			afterpoint;
	int			pos;

	afterpoint = (flags[i_dot]) ? flags[i_precision] : 6;
	d = round_at_precision(d, afterpoint);
	ft_printf_num_to_str((long)d, result, flags);
	if (afterpoint != 0 || flags[i_num_sign] == 1)
	{
		pos = ft_strlen(result);
		result[pos++] = '.';
		d *= (d < 0) ? -1.0 : 1.0;
		while (--afterpoint >= 0)
		{
			d = (d - (long double)(long)(d)) * 10.0;
			result[pos++] = (long)d % 10 + '0';
		}
		result[pos] = '\0';
	}
}

long double		round_at_precision(long double d, int afterpoint)
{
	long double	d_copy;
	long double	add_value;
	long double	sign;
	int			i;

	if (d == 0.0)
		return (d);
	sign = (d < 0.0) ? -1.0 : 1.0;
	d_copy = d;
	i = 0;
	while (i <= afterpoint)
	{
		d = (d - (long double)(long)(d)) * 10.0;
		i++;
	}
	if (ft_round_ldbl(d * 10.0 * sign) < 50)
		return (d_copy);
	add_value = 1.0 * sign;
	i = 0;
	while (i < afterpoint)
	{
		add_value = add_value / 10.0;
		i++;
	}
	return (d_copy + add_value);
}
