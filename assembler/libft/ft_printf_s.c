/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 15:16:51 by ashih             #+#    #+#             */
/*   Updated: 2017/12/26 00:35:02 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_s(va_list *args, int *flags, int *chars_printed)
{
	char	*str;
	int		print_len;
	char	pad_char;

	if (flags[i_l] == 1)
		return (ft_printf_big_s(args, flags, chars_printed));
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
	ft_print_substr(str, print_len, chars_printed);
	if (flags[i_minus] == 1 && flags[i_width] > print_len)
		ft_print_padding(flags[i_width] - print_len, pad_char, chars_printed);
}

void		ft_print_substr(char *str, int len, int *chars_printed)
{
	int		i;

	i = 0;
	while (i < len)
	{
		ft_putchar(str[i++]);
		(*chars_printed)++;
	}
}

void		ft_print_padding(int len, char c, int *chars_printed)
{
	int		i;

	i = 0;
	while (i < len)
	{
		ft_putchar(c);
		i++;
		(*chars_printed)++;
	}
}
