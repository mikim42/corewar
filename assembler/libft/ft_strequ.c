/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:22:05 by ashih             #+#    #+#             */
/*   Updated: 2017/11/28 19:23:41 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (ft_strcmp(s1, s2) == 0)
		return (1);
	else
		return (0);
}