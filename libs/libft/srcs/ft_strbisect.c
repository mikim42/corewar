/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbisect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 11:27:40 by ashih             #+#    #+#             */
/*   Updated: 2018/01/13 18:21:27 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Protip: Use ft_strnchr() to get a pointer for *mid
**
** This amazing thing will make 2 new strings by splitting the original str
** at the *mid position, discarding the char at *mid.
*/

int			ft_strbisect(char *str, char *mid, char **new1, char **new2)
{
	if (str == NULL || mid == NULL)
	{
		*new1 = 0;
		*new2 = 0;
		return (1);
	}
	*new1 = ft_strnew(mid - str);
	ft_strncpy(*new1, str, mid - str);
	*new2 = ft_strnew(ft_strlen(str) - ft_strlen(*new1));
	ft_strcpy(*new2, mid + 1);
	return (0);
}
