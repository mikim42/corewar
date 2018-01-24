/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_o.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 23:23:52 by ashih             #+#    #+#             */
/*   Updated: 2017/12/17 03:31:40 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_o(va_list *args, int *flags, int *chars_printed)
{
	char	result[OCT_STR_MAX_LEN];
	char	*prefix;

	if (flags[i_l] || flags[i_ll] || flags[i_j] || flags[i_z])
		ft_printf_unum_to_oct_str(va_arg(*args, unsigned long), result);
	else if (flags[i_h])
		ft_printf_unum_to_oct_str((unsigned short)va_arg(*args, unsigned int),
				result);
	else if (flags[i_hh])
		ft_printf_unum_to_oct_str((unsigned char)va_arg(*args, unsigned int),
				result);
	else
		ft_printf_unum_to_oct_str(va_arg(*args, unsigned int), result);
	prefix = flags[i_num_sign] ? "0" : "";
	ft_printf_x_format(result, flags, chars_printed, prefix);
}

void		ft_printf_big_o(va_list *args, int *flags, int *chars_printed)
{
	char	result[OCT_STR_MAX_LEN];
	char	*prefix;

	ft_printf_unum_to_oct_str(va_arg(*args, unsigned long), result);
	prefix = flags[i_num_sign] ? "0" : "";
	ft_printf_x_format(result, flags, chars_printed, prefix);
}

void		ft_printf_unum_to_oct_str(unsigned long n, char *result)
{
	int		i;

	i = 0;
	if (n == 0)
		result[i++] = '0';
	else
		while (n != 0)
		{
			result[i++] = n % 8 + '0';
			n = n / 8;
		}
	result[i] = '\0';
	ft_strrev(result);
}

int			octal_prefix_hotfix(char *prefix, char *result, int *flags)
{
	if (!ft_strequ(prefix, "0"))
		return (0);
	if (ft_strequ(result, "0"))
	{
		if (flags[i_dot] && flags[i_precision] == 0)
			return (0);
		else
			return (1);
	}
	if (flags[i_dot] && flags[i_precision] > (int)ft_strlen(result))
		return (1);
	return (0);
}
