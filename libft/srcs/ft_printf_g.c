/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_g.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:42:30 by ashih             #+#    #+#             */
/*   Updated: 2017/12/16 04:25:01 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_printf_g(va_list *args, int *flags, int *chars_printed)
{
	char		result_f[L_DBL_DEC_STR_MAX_LEN];
	char		result_e[L_DBL_DEC_STR_MAX_LEN];
	long double	d;
	int			prec;
	char		*result;

	if (flags[i_dot] == 1)
		flags[i_precision]--;
	d = flags[i_big_l] ? va_arg(*args, long double) : va_arg(*args, double);
	ft_printf_g_l_dbl_to_str(d, result_f, flags);
	ft_printf_g_l_dbl_to_sn_str(d, result_e, flags, 0);
	hotfix_exp_1(result_e);
	trim_zeroes(result_f, flags);
	prec = (flags[i_dot]) ? flags[i_precision] : 5;
	result = count_left_len(d) > prec ? result_e : result_f;
	flags[i_dot] = 0;
	ft_printf_x_format(result, flags, chars_printed, "");
}

void			ft_printf_big_g(va_list *args, int *flags, int *chars_printed)
{
	char		result_f[L_DBL_DEC_STR_MAX_LEN];
	char		result_e[L_DBL_DEC_STR_MAX_LEN];
	long double	d;
	int			prec;
	char		*result;

	if (flags[i_dot] == 1)
		flags[i_precision]--;
	d = flags[i_big_l] ? va_arg(*args, long double) : va_arg(*args, double);
	ft_printf_g_l_dbl_to_str(d, result_f, flags);
	ft_printf_g_l_dbl_to_sn_str(d, result_e, flags, 1);
	hotfix_exp_1(result_e);
	trim_zeroes(result_f, flags);
	prec = (flags[i_dot]) ? flags[i_precision] : 5;
	result = count_left_len(d) > prec ? result_e : result_f;
	flags[i_dot] = 0;
	ft_printf_x_format(result, flags, chars_printed, "");
}
