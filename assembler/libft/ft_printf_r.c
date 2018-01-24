/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 01:24:06 by ashih             #+#    #+#             */
/*   Updated: 2017/12/26 00:34:53 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_r(va_list *args, int *flags, int *chars_printed)
{
	char	*str;
	int		print_len;
	char	pad_char;

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
	ft_print_substr_r(str, print_len, chars_printed);
	if (flags[i_minus] == 1 && flags[i_width] > print_len)
		ft_print_padding(flags[i_width] - print_len, pad_char, chars_printed);
}

void		ft_print_substr_r(char *str, int len, int *chars_printed)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (ft_isprint(str[i]))
			ft_putchar(str[i]);
		else
			ft_putchar('.');
		i++;
		(*chars_printed)++;
	}
}
