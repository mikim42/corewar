/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:38:24 by ashih             #+#    #+#             */
/*   Updated: 2017/11/27 17:06:03 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_ptr;
	char	*src_ptr;
	int		i;

	dst_ptr = (char *)dst;
	src_ptr = (char *)src;
	if (dst_ptr > src_ptr)
	{
		i = len - 1;
		while (i >= 0)
		{
			dst_ptr[i] = src_ptr[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)len)
		{
			dst_ptr[i] = src_ptr[i];
			i++;
		}
	}
	return (dst);
}
