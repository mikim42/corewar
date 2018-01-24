/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 23:38:37 by ashih             #+#    #+#             */
/*   Updated: 2017/12/04 20:50:30 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*node;
	t_list	*temp;

	if (alst == NULL || *alst == NULL)
		return ;
	node = *alst;
	*alst = NULL;
	while (node != NULL)
	{
		if (node->content != NULL && del != NULL)
			del(node->content, node->content_size);
		temp = node;
		node = node->next;
		free(temp);
	}
}
