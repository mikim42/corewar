/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 06:38:22 by ashih             #+#    #+#             */
/*   Updated: 2017/11/28 22:50:36 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*make_zero_str(void)
{
	char	*result;

	result = malloc(sizeof(char) * 2);
	if (result == NULL)
		return (NULL);
	result[0] = '0';
	result[1] = '\0';
	return (result);
}

static int	count_places(int n)
{
	int		places;
	int		sign;

	places = 0;
	sign = (n < 0) ? -1 : 1;
	while (n != 0)
	{
		places++;
		n = n / 10;
	}
	places += (sign == -1) ? 1 : 0;
	return (places);
}

char		*ft_itoa(int n)
{
	char	*result;
	int		places;
	int		sign;

	if (n == 0)
		return (make_zero_str());
	places = count_places(n);
	sign = (n < 0) ? -1 : 1;
	result = malloc(sizeof(char) * (places + 1));
	if (result == NULL)
		return (NULL);
	result[places--] = '\0';
	while (n != 0)
	{
		result[places--] = n % 10 * sign + '0';
		n = n / 10;
	}
	if (sign == -1)
		result[places] = '-';
	return (result);
}
