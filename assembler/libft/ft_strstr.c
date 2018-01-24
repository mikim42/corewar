/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 22:07:28 by ashih             #+#    #+#             */
/*   Updated: 2017/11/27 23:09:59 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_match(const char *big, const char *little)
{
	int		i;

	i = 0;
	while (little[i])
	{
		if (big[i] != little[i])
			return (0);
		i++;
	}
	return (1);
}

char		*ft_strstr(const char *big, const char *little)
{
	int		i;

	if (!little[0])
		return ((char *)big);
	i = 0;
	while (big[i])
	{
		if (big[i] == little[0])
		{
			if (find_match(big + i, little))
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
