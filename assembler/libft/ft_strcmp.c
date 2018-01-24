/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 21:36:49 by ashih             #+#    #+#             */
/*   Updated: 2017/11/27 21:54:58 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	int				i;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	i = 0;
	while (s1_ptr[i] != '\0' && s1_ptr[i] == s2_ptr[i])
		i++;
	return (s1_ptr[i] - s2_ptr[i]);
}
