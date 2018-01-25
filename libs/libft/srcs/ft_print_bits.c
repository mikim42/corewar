/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:07:53 by ashih             #+#    #+#             */
/*   Updated: 2017/11/29 15:22:27 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_print_bits(unsigned char octet)
{
	char	buffer[8];
	int		i;

	i = 0;
	while (octet != 0)
	{
		buffer[i++] = octet % 2 + '0';
		octet = octet / 2;
	}
	while (i < 8)
		buffer[i++] = '0';
	i = 7;
	while (i >= 0)
		ft_putchar(buffer[i--]);
}
