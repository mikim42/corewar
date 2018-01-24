/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_array_length.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 03:50:10 by ashih             #+#    #+#             */
/*   Updated: 2017/12/25 03:51:47 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_char_array_length(char **array)
{
	int		i;

	if (array == 0)
	{
		ft_putstr(" *DEBUG: ft_char_array_length(): array is NULL");
		return (0);
	}
	i = 0;
	while (array[i])
		i++;
	return (i);
}
