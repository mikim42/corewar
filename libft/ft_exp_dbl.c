/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_dbl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 17:55:33 by ashih             #+#    #+#             */
/*   Updated: 2018/01/13 17:56:44 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double				ft_exp_dbl(int base, unsigned int power)
{
	double			product;
	unsigned int	i;

	if (base == 0 && power == 0)
		return (1.0);
	if (base == 0)
		return (0.0);
	if (power == 0)
		return (1.0);
	product = 1.0;
	i = 0;
	while (i < power)
	{
		product *= (double)base;
		i++;
	}
	return (product);
}
