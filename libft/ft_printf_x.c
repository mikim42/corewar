/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 17:27:30 by ashih             #+#    #+#             */
/*   Updated: 2017/12/17 03:34:41 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char g_hextable_upper[] = "0123456789ABCDEF";
const char g_hextable_lower[] = "0123456789abcdef";

void		ft_printf_x(va_list *args, int *flags, int *chars_printed)
{
	char	result[HEX_STR_MAX_LEN];
	char	*prefix;

	if (flags[i_l] || flags[i_ll] || flags[i_j] || flags[i_z])
		ft_printf_unum_to_hex_str(va_arg(*args, unsigned long), result,
				flags, 0);
	else if (flags[i_h])
		ft_printf_unum_to_hex_str((unsigned short)va_arg(*args, unsigned int),
				result, flags, 0);
	else if (flags[i_hh])
		ft_printf_unum_to_hex_str((unsigned char)va_arg(*args, unsigned int),
				result, flags, 0);
	else
		ft_printf_unum_to_hex_str(va_arg(*args, unsigned int), result,
				flags, 0);
	prefix = flags[i_num_sign] ? "0x" : "";
	ft_printf_x_format(result, flags, chars_printed, prefix);
}

void		ft_printf_big_x(va_list *args, int *flags, int *chars_printed)
{
	char	result[HEX_STR_MAX_LEN];
	char	*prefix;

	if (flags[i_hh])
		ft_printf_unum_to_hex_str((unsigned char)va_arg(*args, unsigned int),
				result, flags, 1);
	else if (flags[i_h])
		ft_printf_unum_to_hex_str((unsigned short)va_arg(*args, unsigned int),
				result, flags, 1);
	else if (flags[i_l] || flags[i_ll] || flags[i_j] || flags[i_z])
		ft_printf_unum_to_hex_str(va_arg(*args, unsigned long),
				result, flags, 1);
	else
		ft_printf_unum_to_hex_str(va_arg(*args, unsigned int),
				result, flags, 1);
	prefix = flags[i_num_sign] ? "0X" : "";
	ft_printf_x_format(result, flags, chars_printed, prefix);
}

void		ft_printf_unum_to_hex_str(unsigned long n, char *result, int *flags,
		int big_x)
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
			result[i++] = (big_x == 1) ? g_hextable_upper[n % 16] :
				g_hextable_lower[n % 16];
			n = n / 16;
		}
	result[i] = '\0';
	ft_strrev(result);
}

void		ft_printf_x_format(char *result, int *flags, int *chars_printed,
		char *prefix)
{
	int		print_len;
	char	pad_char;

	pad_char = (flags[i_zero] && !flags[i_minus] && !flags[i_dot]) ? '0' : ' ';
	if (octal_prefix_hotfix(prefix, result, flags))
		prefix = "";
	print_len = ft_strlen(prefix);
	print_len += (flags[i_dot]) ? ft_printf_str_prec_len(result,
			flags[i_precision]) : ft_strlen(result);
	if (flags[i_num_sign] && pad_char == '0')
		ft_putstr(prefix);
	if (flags[i_minus] == 0 && flags[i_width] > print_len)
		ft_print_padding(flags[i_width] - print_len, pad_char, chars_printed);
	if (flags[i_num_sign] && pad_char == ' ')
		ft_putstr(prefix);
	(flags[i_dot]) ? ft_printf_putstr_prec(result, flags[i_precision]) :
	ft_putstr(result);
	*chars_printed += print_len;
	if (flags[i_minus] == 1 && flags[i_width] > print_len)
		ft_print_padding(flags[i_width] - print_len, pad_char, chars_printed);
}
