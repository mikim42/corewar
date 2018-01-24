/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_first.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:51:39 by ashih             #+#    #+#             */
/*   Updated: 2017/11/29 16:08:50 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_lst_remove_first(t_list **alst)
{
	void	*data;
	t_list	*temp;

	if (alst == NULL || *alst == NULL)
		return (NULL);
	data = (*alst)->content;
	temp = *alst;
	*alst = (*alst)->next;
	free(temp);
	return (data);
}
