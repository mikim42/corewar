/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 00:09:51 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 15:52:52 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Return 1 if the str doesn't even have a valid digit, AND does not overflow to
** a negative number;
** Otherwise, return 0, and store the int value at *n;
*/

int		ft_atoi_check(char *str, int *n)
{
	int		total;
	int		sign;

	total = 0;
	sign = 1;
	*n = 0;
	if (*str == '-')
		sign = -1;
	else if (*str == '+')
		sign = 1;
	else
		str--;
	str++;
	if (!ft_isdigit(*str))
		return (1);
	while (ft_isdigit(*str))
		total = total * 10 + (*str++ - '0');
	if ((*n = total * sign) < 0)
	{
		*n = 0;
		return (1);
	}
	if (*str != '\0')
		return (1);
	return (0);
}
