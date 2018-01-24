/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 23:49:43 by ashih             #+#    #+#             */
/*   Updated: 2017/11/28 23:58:17 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	add_last(t_list **head, t_list *node)
{
	t_list	*temp;

	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = node;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;

	if (f == NULL)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		add_last(&new_lst, f(lst));
		lst = lst->next;
	}
	return (new_lst);
}
