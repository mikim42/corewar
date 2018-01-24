/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:27:40 by ashih             #+#    #+#             */
/*   Updated: 2018/01/13 18:21:40 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnchr(char *str, int c, int n)
{
	int		i;

	if (n <= 0)
		return (NULL);
	i = 0;
	while (1)
	{
		str = ft_strchr(str, c);
		if (str == NULL)
			return (NULL);
		i++;
		if (i >= n)
			return (str);
		str++;
	}
}
