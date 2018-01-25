/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 22:47:53 by ashih             #+#    #+#             */
/*   Updated: 2017/11/28 21:59:24 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	total;
	int	sign;

	total = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
			*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	else if (*str == '+')
		sign = 1;
	else
		str--;
	str++;
	while ('0' <= *str && *str <= '9')
	{
		total = total * 10 + (*str - '0');
		str++;
	}
	return (total * sign);
}
