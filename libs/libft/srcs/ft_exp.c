/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:00:20 by ashih             #+#    #+#             */
/*   Updated: 2017/11/29 15:06:36 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_exp(int base, unsigned int power)
{
	int				product;
	unsigned int	i;

	if (base == 0 && power == 0)
		return (1);
	if (base == 0)
		return (0);
	if (power == 0)
		return (1);
	product = 1;
	i = 0;
	while (i < power)
	{
		product *= base;
		i++;
	}
	return (product);
}
