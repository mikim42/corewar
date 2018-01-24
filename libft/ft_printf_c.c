/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 01:36:36 by ashih             #+#    #+#             */
/*   Updated: 2017/12/26 00:31:31 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_c(va_list *args, int *flags, int *chars_printed)
{
	char	pad_char;

	if (flags[i_l] == 1)
		return (ft_printf_big_c(args, flags, chars_printed));
	pad_char = (flags[i_zero] && !flags[i_minus]) ? '0' : ' ';
	if (flags[i_minus] == 0 && flags[i_width] > 1)
		ft_print_padding(flags[i_width] - 1, pad_char, chars_printed);
	ft_putchar((char)va_arg(*args, int));
	(*chars_printed)++;
	if (flags[i_minus] == 1 && flags[i_width] > 1)
		ft_print_padding(flags[i_width] - 1, pad_char, chars_printed);
}
