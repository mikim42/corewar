/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_hotfix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 17:38:28 by ashih             #+#    #+#             */
/*   Updated: 2018/01/30 17:38:44 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		fail_cor_ender(char *filename)
{
	char	ender[5];
	int		i;

	if (ft_strlen(filename) < 4)
		return (1);
	ft_strcpy(ender, filename + ft_strlen(filename) - 4);
	i = 0;
	while (++i < 4)
		ender[i] = (char)ft_toupper(ender[i]);
	return (ft_strequ(".COR", ender) ? 0 : 1);
}
