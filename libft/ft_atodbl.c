/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atodbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 17:42:06 by ashih             #+#    #+#             */
/*   Updated: 2018/01/13 18:28:16 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		add_decimal(double *total, const char *str, int sign)
{
	int			i;

	if (*str != '.')
		return ;
	i = 1;
	while (ft_isdigit(*(++str)))
		*total += (double)(*str - '0') / ft_exp_dbl(10, i++) * sign;
}

double			ft_atodbl(const char *str)
{
	double		total;
	int			subtotal;
	int			sign;

	subtotal = 0;
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
	while (ft_isdigit(*str))
	{
		subtotal = subtotal * 10.0 + (double)(*str - '0');
		str++;
	}
	total = (double)subtotal * sign;
	add_decimal(&total, str, sign);
	return (total);
}
