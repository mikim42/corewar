/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_e.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 18:49:49 by ashih             #+#    #+#             */
/*   Updated: 2017/12/15 21:31:34 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_e(va_list *args, int *flags, int *chars_printed)
{
	char	result[L_DBL_DEC_STR_MAX_LEN];

	if (flags[i_big_l] == 1)
		ft_printf_l_dbl_to_sn_str(va_arg(*args, long double), result, flags, 0);
	else
		ft_printf_l_dbl_to_sn_str(va_arg(*args, double), result, flags, 0);
	flags[i_dot] = 0;
	ft_printf_x_format(result, flags, chars_printed, "");
}

void		ft_printf_big_e(va_list *args, int *flags, int *chars_printed)
{
	char	result[L_DBL_DEC_STR_MAX_LEN];

	if (flags[i_big_l] == 1)
		ft_printf_l_dbl_to_sn_str(va_arg(*args, long double), result, flags, 1);
	else
		ft_printf_l_dbl_to_sn_str(va_arg(*args, double), result, flags, 1);
	flags[i_dot] = 0;
	ft_printf_x_format(result, flags, chars_printed, "");
}

void		ft_printf_l_dbl_to_sn_str(long double d, char *result, int *flags,
		int big_e)
{
	int		afterpoint;
	int		exp;
	int		pos;

	exp = 0;
	afterpoint = (flags[i_dot]) ? flags[i_precision] : 6;
	put_in_scientific_notation(&d, &exp);
	d = round_at_precision(d, afterpoint);
	put_in_scientific_notation(&d, &exp);
	ft_printf_num_to_str((long)d, result, flags);
	if (afterpoint != 0 || flags[i_num_sign] == 1)
	{
		pos = ft_strlen(result);
		result[pos++] = '.';
		d *= (d < 0) ? -1 : 1;
		while (--afterpoint >= 0)
		{
			d = (d - (long double)(long)(d)) * 10.0;
			result[pos++] = (int)d % 10 + '0';
		}
		result[pos] = '\0';
	}
	float_exp_to_str(exp, result + ft_strlen(result), flags, big_e);
}

void		put_in_scientific_notation(long double *d, int *exp)
{
	int		sign;

	if (*d == 0.0)
		return ;
	sign = (*d < 0.0) ? -1 : 1;
	*d *= (long double)sign;
	while (*d >= 10.0)
	{
		*d /= 10.0;
		(*exp)++;
	}
	while (*d < 1.0)
	{
		*d *= 10.0;
		(*exp)--;
	}
	*d *= (long double)sign;
}

void		float_exp_to_str(int exp, char *result, int *flags, int big_e)
{
	int		sign;

	sign = (exp < 0) ? -1 : 1;
	*result++ = (big_e == 1) ? 'E' : 'e';
	flags[i_plus] = 0;
	flags[i_space] = 0;
	flags[i_apostrophe] = 0;
	*result++ = (sign == -1) ? '-' : '+';
	exp *= sign;
	if (exp < 10)
		*result++ = '0';
	ft_printf_num_to_str(exp, result, flags);
}
