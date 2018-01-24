/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 18:44:43 by ashih             #+#    #+#             */
/*   Updated: 2017/11/27 19:23:32 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	temp = ft_strlen(dst) + ft_strlen(src);
	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (i < size - 1 && src[j] != '\0')
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (temp);
}
