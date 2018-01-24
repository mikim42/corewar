/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 22:25:15 by ashih             #+#    #+#             */
/*   Updated: 2017/11/28 22:49:23 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	buffer[15];
	int		sign;
	int		i;

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	sign = (n < 0) ? -1 : 1;
	i = 0;
	while (n != 0)
	{
		buffer[i++] = n % 10 * sign + '0';
		n = n / 10;
	}
	i--;
	if (sign == -1)
		ft_putchar_fd('-', fd);
	while (i >= 0)
		ft_putchar_fd(buffer[i--], fd);
}
