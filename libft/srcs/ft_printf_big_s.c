/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_big_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 15:16:51 by ashih             #+#    #+#             */
/*   Updated: 2017/12/17 01:53:18 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_big_s(va_list *args, int *flags, int *chars_printed)
{
	wchar_t	*wstr;
	int		print_len;
	char	pad_char;

	wstr = va_arg(*args, wchar_t *);
	if (wstr == 0)
		wstr = L"(null)";
	pad_char = (flags[i_zero] && !flags[i_minus]) ? '0' : ' ';
	if (flags[i_dot] == 1)
		print_len = ft_print_subwstr_char_count(wstr, flags[i_precision]);
	else
		print_len = ft_wstr_len(wstr);
	if (flags[i_minus] == 0 && flags[i_width] > print_len)
		ft_print_padding(flags[i_width] - print_len, pad_char, chars_printed);
	ft_print_subwstr(wstr, print_len, chars_printed);
	if (flags[i_minus] == 1 && flags[i_width] > print_len)
		ft_print_padding(flags[i_width] - print_len, pad_char, chars_printed);
}

int			ft_wstr_len(wchar_t *wstr)
{
	int		i;
	int		total;

	if (wstr == 0)
		return (0);
	i = 0;
	total = 0;
	while (wstr[i])
	{
		total += ft_wchar_len(wstr[i]);
		i++;
	}
	return (total);
}

int			ft_print_subwstr_char_count(wchar_t *wstr, int char_len)
{
	int		i;
	int		total_printed;

	if (wstr == 0)
		return (0);
	i = 0;
	total_printed = 0;
	while (wstr[i])
	{
		if (ft_wchar_len(wstr[i]) + total_printed > char_len)
			break ;
		total_printed += ft_wchar_len(wstr[i]);
		i++;
	}
	return (total_printed);
}

void		ft_print_subwstr(wchar_t *wstr, int char_len, int *chars_printed)
{
	int		i;
	int		total_printed;

	if (wstr == 0)
	{
		ft_putstr("(null)");
		*chars_printed += 6;
		return ;
	}
	i = 0;
	total_printed = 0;
	while (wstr[i])
	{
		if (ft_wchar_len(wstr[i]) + total_printed > char_len)
			return ;
		total_printed += ft_wchar_len(wstr[i]);
		ft_put_wchar(wstr[i]);
		*chars_printed += ft_wchar_len(wstr[i]);
		i++;
	}
}
