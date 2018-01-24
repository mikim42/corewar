/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 23:26:50 by ashih             #+#    #+#             */
/*   Updated: 2017/12/01 23:30:19 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_prime(int n)
{
	int	possible_factor;
	int	end_case;

	if (n <= 1)
		return (0);
	if (n == 2)
		return (1);
	if (n % 2 == 0)
		return (0);
	possible_factor = 3;
	end_case = ft_sqrt(n);
	while (possible_factor <= end_case)
	{
		if (n % possible_factor == 0)
			return (0);
		possible_factor += 2;
	}
	return (1);
}
