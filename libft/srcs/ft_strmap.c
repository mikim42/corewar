/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:14:45 by ashih             #+#    #+#             */
/*   Updated: 2017/11/28 17:28:11 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	int		i;

	if (s == NULL)
		return (NULL);
	new = ft_strdup(s);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (new[i])
	{
		new[i] = f(new[i]);
		i++;
	}
	return (new);
}
