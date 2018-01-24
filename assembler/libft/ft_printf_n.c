/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 22:04:45 by ashih             #+#    #+#             */
/*   Updated: 2017/12/17 03:33:39 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_n(va_list *args, int *flags, int *chars_printed)
{
	if (flags[i_j] == 1)
		*(va_arg(*args, intmax_t *)) = *chars_printed;
	else if (flags[i_z] == 1)
		*(va_arg(*args, size_t *)) = *chars_printed;
	else if (flags[i_ll] == 1)
		*(va_arg(*args, long long *)) = *chars_printed;
	else if (flags[i_l] == 1)
		*(va_arg(*args, long *)) = *chars_printed;
	else if (flags[i_h] == 1)
		*(va_arg(*args, short *)) = *chars_printed;
	else if (flags[i_hh] == 1)
		*(va_arg(*args, char *)) = *chars_printed;
	else
		*(va_arg(*args, int *)) = *chars_printed;
}
