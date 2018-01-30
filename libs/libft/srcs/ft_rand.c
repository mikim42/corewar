/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 19:45:05 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 19:48:48 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	g_next = 1;

/*
**	ft_srand() exists entirely for compatibility with systems that don't have
**	/dev/urandom, or don't have /dev/urandom available to the caller.
**	Because of this, ft_srand() should still be called once to ensure
**	compatibility between systems.
*/

void					ft_srand(unsigned long seed)
{
	g_next = seed;
}

unsigned int			ft_rand(void)
{
	static int			fd;
	unsigned int		result;

	if (fd == 0)
		fd = open("/dev/urandom", O_RDONLY, 0);
	if (fd < 0)
		return ((unsigned int)(g_next = g_next * 1103515245 + 12345));
	read(fd, &result, sizeof(unsigned int));
	return (result);
}
