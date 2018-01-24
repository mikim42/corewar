/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 23:35:42 by ashih             #+#    #+#             */
/*   Updated: 2017/12/17 00:21:21 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_p(va_list *args, int *flags, int *chars_printed)
{
	char	result[HEX_STR_MAX_LEN];

	ft_printf_unum_to_hex_str((unsigned long)va_arg(*args, void *),
			result, flags, 0);
	flags[i_num_sign] = 1;
	ft_printf_x_format(result, flags, chars_printed, "0x");
}
