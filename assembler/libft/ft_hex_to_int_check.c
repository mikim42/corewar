/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_to_int_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 00:11:16 by ashih             #+#    #+#             */
/*   Updated: 2018/01/14 23:54:27 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Return 1 if the str doesn't even have a valid digit;
** Otherwise, return 0, and store the int value at *n
*/

int						ft_hex_to_int_check(char *str, int *n)
{
	const char			hextable[] = "0123456789ABCDEF";
	unsigned int		total;

	*n = 0;
	total = 0;
	if (ft_strnequ(str, "0x", 2))
		str += 2;
	else
		return (1);
	if (!ft_strchr(hextable, ft_toupper(*str)))
		return (1);
	while (*str && ft_strchr(hextable, ft_toupper(*str)))
	{
		total = total * 16 +
			(ft_strchr(hextable, ft_toupper(*str)) - hextable);
		str++;
	}
	if (*str != '\0')
		return (1);
	*n = total;
	return (0);
}
