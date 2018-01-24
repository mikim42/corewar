/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 16:45:29 by ashih             #+#    #+#             */
/*   Updated: 2017/11/28 17:28:48 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*new;

	new = malloc(sizeof(char) * (size + 1));
	if (new == NULL)
		return (NULL);
	ft_bzero(new, size + 1);
	return (new);
}
