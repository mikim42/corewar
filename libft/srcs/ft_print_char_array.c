/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 06:07:51 by ashih             #+#    #+#             */
/*   Updated: 2017/12/25 06:09:59 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_char_array(char **array)
{
	int	i;

	if (array == 0)
		return ;
	i = 0;
	while (array[i] != 0)
	{
		ft_putstr(array[i]);
		ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}
