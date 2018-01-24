/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:06:00 by ashih             #+#    #+#             */
/*   Updated: 2017/11/27 10:47:26 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*char_ptr;
	size_t			i;

	char_ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		*char_ptr = c;
		char_ptr++;
		i++;
	}
	return (b);
}
