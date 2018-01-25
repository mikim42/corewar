/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 22:07:28 by ashih             #+#    #+#             */
/*   Updated: 2017/11/28 16:00:55 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_match(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	while (little[i])
	{
		if (big[i] != little[i] || i >= len)
			return (0);
		i++;
	}
	return (1);
}

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!little[0])
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			if (find_match(big + i, little, len - i))
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
