/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_any_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 23:34:31 by ashih             #+#    #+#             */
/*   Updated: 2017/12/17 01:01:37 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_any_char(char c, int *flags, int *chars_printed)
{
	char	pad_char;

	pad_char = (flags[i_zero] && !flags[i_minus]) ? '0' : ' ';
	if (flags[i_minus] == 0 && flags[i_width] > 1)
		ft_print_padding(flags[i_width] - 1, pad_char, chars_printed);
	ft_putchar(c);
	(*chars_printed)++;
	if (flags[i_minus] == 1 && flags[i_width] > 1)
		ft_print_padding(flags[i_width] - 1, pad_char, chars_printed);
}
