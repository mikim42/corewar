/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_k.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 01:34:00 by ashih             #+#    #+#             */
/*   Updated: 2017/12/26 00:34:36 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_printf_k(va_list *args, int *flags, int *chars_printed)
{
	char		*str;
	int			print_len;
	char		pad_char;

	str = va_arg(*args, char *);
	if (str == 0)
		str = "(null)";
	pad_char = (flags[i_zero] && !flags[i_minus]) ? '0' : ' ';
	if (flags[i_dot] == 1)
		print_len = ft_min((int)ft_strlen(str), flags[i_precision]);
	else
		print_len = ft_strlen(str);
	if (flags[i_minus] == 0 && flags[i_width] > print_len)
		ft_print_padding(flags[i_width] - print_len, pad_char, chars_printed);
	ft_print_substr_k(str, print_len, chars_printed, 0);
	if (flags[i_minus] == 1 && flags[i_width] > print_len)
		ft_print_padding(flags[i_width] - print_len, pad_char, chars_printed);
}

void			ft_printf_big_k(va_list *args, int *flags, int *chars_printed)
{
	char		*str;
	int			print_len;
	char		pad_char;

	str = va_arg(*args, char *);
	if (str == 0)
		str = "(null)";
	pad_char = (flags[i_zero] && !flags[i_minus]) ? '0' : ' ';
	if (flags[i_dot] == 1)
		print_len = ft_min((int)ft_strlen(str), flags[i_precision]);
	else
		print_len = ft_strlen(str);
	if (flags[i_minus] == 0 && flags[i_width] > print_len)
		ft_print_padding(flags[i_width] - print_len, pad_char, chars_printed);
	ft_print_substr_k(str, print_len, chars_printed, 1);
	if (flags[i_minus] == 1 && flags[i_width] > print_len)
		ft_print_padding(flags[i_width] - print_len, pad_char, chars_printed);
}

void			ft_print_substr_k(char *str, int len, int *chars_printed,
		int big_k)
{
	int			i;
	const char	*hextable;

	i = 0;
	hextable = (big_k == 1) ? g_hextable_upper : g_hextable_lower;
	while (i < len)
	{
		ft_putchar(hextable[str[i] / 16]);
		ft_putchar(hextable[str[i] % 16]);
		i++;
		(*chars_printed) += 2;
	}
}
