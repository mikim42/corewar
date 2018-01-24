/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add_last.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:38:08 by ashih             #+#    #+#             */
/*   Updated: 2017/11/29 15:43:51 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lst_add_last(t_list **alst, t_list *new)
{
	t_list	*current;

	if (new == 0)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	current = *alst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}
