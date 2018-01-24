/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:57:58 by ashih             #+#    #+#             */
/*   Updated: 2017/11/27 14:05:58 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*char_ptr;
	size_t			i;

	char_ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (char_ptr[i] == (unsigned char)c)
			return (char_ptr + i);
		i++;
	}
	return (NULL);
}
