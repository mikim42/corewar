/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_big_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 21:41:18 by ashih             #+#    #+#             */
/*   Updated: 2017/12/17 00:57:13 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_big_c(va_list *args, int *flags, int *chars_printed)
{
	wchar_t	wc;
	int		char_len;
	char	pad_char;

	wc = va_arg(*args, wchar_t);
	char_len = ft_wchar_len(wc);
	pad_char = (flags[i_zero] && !flags[i_minus]) ? '0' : ' ';
	if (flags[i_minus] == 0 && flags[i_width] > char_len)
		ft_print_padding(flags[i_width] - char_len, pad_char, chars_printed);
	ft_put_wchar(wc);
	*chars_printed += char_len;
	if (flags[i_minus] == 1 && flags[i_width] > char_len)
		ft_print_padding(flags[i_width] - char_len, pad_char, chars_printed);
}

int			ft_wchar_len(wchar_t wc)
{
	if (wc <= 0x7F)
		return (1);
	else if (wc <= 0x7FF)
		return (2);
	else if (wc <= 0xFFFF)
		return (3);
	else
		return (4);
}

void		ft_put_wchar(wchar_t wc)
{
	if (wc <= 0x7F)
		ft_putchar((unsigned char)wc);
	else if (wc <= 0x7FF)
	{
		ft_putchar((unsigned char)(0xC0 | (wc >> 6)));
		ft_putchar((unsigned char)(0x80 | (wc & 0x3F)));
	}
	else if (wc <= 0xFFFF)
	{
		ft_putchar((unsigned char)(0xE0 | (wc >> 12)));
		ft_putchar((unsigned char)(0x80 | ((wc >> 6) & 0x3F)));
		ft_putchar((unsigned char)(0x80 | (wc & 0x3F)));
	}
	else
	{
		ft_putchar((unsigned char)(0xF0 | (wc >> 18)));
		ft_putchar((unsigned char)(0x80 | ((wc >> 12) & 0x3F)));
		ft_putchar((unsigned char)(0x80 | ((wc >> 6) & 0x3F)));
		ft_putchar((unsigned char)(0x80 | (wc & 0x3F)));
	}
}
