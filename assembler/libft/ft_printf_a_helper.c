/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_a_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 16:33:52 by ashih             #+#    #+#             */
/*   Updated: 2017/12/16 02:39:04 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_l_dbl_to_hex_str(long double d, char *result, int *flags,
		int big_p)
{
	int		afterpoint;
	int		exp;
	int		pos;

	if (d == 0.0)
		return (ft_printf_hex_zero_to_str(result, big_p));
	afterpoint = (flags[i_dot]) ? flags[i_precision] : 50;
	put_in_hex_scientific_notation(&d, &exp);
	ft_printf_hex_prefix_to_str((long)d, result, flags, big_p);
	if (afterpoint != 0 || flags[i_num_sign] == 1)
	{
		pos = ft_strlen(result);
		result[pos++] = '.';
		d *= (d < 0) ? -1 : 1;
		while (--afterpoint >= 0)
		{
			d = (d - (long double)(long)(d)) * 16.0;
			if (d == 0.0 && flags[i_dot] == 0)
				break ;
			result[pos++] = (big_p == 1) ? g_hextable_upper[(int)d % 16] :
				g_hextable_lower[(int)d % 16];
		}
		1 ? (result[pos] = '\0') || trim_zeroes(result, flags) : 0;
	}
	float_hex_exp_to_str(exp, result + ft_strlen(result), flags, big_p);
}

void		ft_printf_hex_prefix_to_str(long n, char *result, int *flags,
		int big_p)
{
	if (n < 0.0)
		*result++ = '-';
	else if (flags[i_plus] == 1)
		*result++ = '+';
	else if (flags[i_space] == 1)
		*result++ = ' ';
	*result++ = '0';
	*result++ = big_p == 1 ? 'X' : 'x';
	*result++ = '1';
	*result = '\0';
}

void		put_in_hex_scientific_notation(long double *d, int *exp)
{
	int		sign;

	*exp = 0;
	if (*d == 0.0)
		return ;
	sign = (*d < 0.0) ? -1 : 1;
	*d *= (long double)sign;
	while (*d >= 2.0)
	{
		*d /= 2.0;
		(*exp)++;
	}
	while (*d < 1.0)
	{
		*d *= 2.0;
		(*exp)--;
	}
	*d *= (long double)sign;
}

void		float_hex_exp_to_str(int exp, char *result, int *flags, int big_p)
{
	int		sign;

	sign = (exp < 0) ? -1 : 1;
	*result++ = (big_p == 1) ? 'P' : 'p';
	flags[i_plus] = 0;
	flags[i_space] = 0;
	flags[i_apostrophe] = 0;
	*result++ = (sign == -1) ? '-' : '+';
	exp *= sign;
	ft_printf_num_to_str(exp, result, flags);
}

void		ft_printf_hex_zero_to_str(char *result, int big_p)
{
	*result++ = '0';
	*result++ = (big_p == 1) ? 'X' : 'x';
	*result++ = '0';
	*result++ = (big_p == 1) ? 'P' : 'p';
	*result++ = '+';
	*result++ = '0';
	*result++ = '\0';
}
