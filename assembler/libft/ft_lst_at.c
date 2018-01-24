/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 02:45:51 by ashih             #+#    #+#             */
/*   Updated: 2017/12/24 22:05:57 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_lst_at(t_list *alst, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		if (alst->next == NULL)
		{
			ft_putstr("*DEBUG: ft_lst_at() returned NULL\n");
			return (NULL);
		}
		alst = alst->next;
		i++;
	}
	return (alst->content);
}
