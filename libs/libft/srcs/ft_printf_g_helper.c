/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_g_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 04:25:05 by ashih             #+#    #+#             */
/*   Updated: 2017/12/16 04:26:26 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_printf_g_l_dbl_to_str(long double d, char *result,
		int *flags)
{
	int			afterpoint;
	int			pos;

	afterpoint = (flags[i_dot]) ? flags[i_precision] : 5;
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

void			ft_printf_g_l_dbl_to_sn_str(long double d, char *result,
		int *flags, int big_e)
{
	int			afterpoint;
	int			exp;
	int			pos;

	exp = 0;
	afterpoint = (flags[i_dot]) ? flags[i_precision] : 5;
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
	trim_zeroes(result, flags);
	float_exp_to_str(exp, result + ft_strlen(result), flags, big_e);
}

int				count_left_len(long double d)
{
	int			total;
	long		l;

	total = 0;
	l = (long)d;
	if (l == 0)
		return (1);
	if (l < 0)
		total++;
	while (l != 0)
	{
		total++;
		l /= 10;
	}
	return (total);
}

int				trim_zeroes(char *result, int *flags)
{
	int			i;

	if (flags[i_dot] == 1 & flags[i_precision] == 0)
		return (0);
	i = ft_strlen(result);
	i--;
	while (result[i] == '0')
		result[i--] = '\0';
	if (result[i] == '.' && flags[i_num_sign] == 0)
		result[i] = '\0';
	return (1);
}

void			hotfix_exp_1(char *result)
{
	int			i;

	i = 0;
	ft_strrev(result);
	if (ft_strnequ(result, "10+", 3) && ft_strchr(result, '.') != 0)
	{
		ft_strrev(result);
		while (result[i] != '.')
			i++;
		result[i] = result[i + 1];
		i++;
		result[i++] = '.';
		while (!(result[i] == 'e' || result[i] == 'E'))
			i++;
		result[i] = '\0';
		if (result[i - 1] == '.')
			result[i - 1] = '\0';
		return ;
	}
	ft_strrev(result);
}
