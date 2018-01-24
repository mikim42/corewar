/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 21:46:51 by ashih             #+#    #+#             */
/*   Updated: 2017/11/28 16:11:35 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	size_t			i;

	if (n == 0)
		return (0);
	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	i = 0;
	while (i < n && s1_ptr[i] != '\0' && s1_ptr[i] == s2_ptr[i])
		i++;
	if (i >= n)
		return (0);
	else
		return (s1_ptr[i] - s2_ptr[i]);
}
