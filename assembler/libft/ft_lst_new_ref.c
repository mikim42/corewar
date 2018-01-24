/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new_ref.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 23:19:40 by ashih             #+#    #+#             */
/*   Updated: 2017/12/04 14:25:08 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lst_new_ref(void const *content, size_t content_size)
{
	t_list	*new;

	if ((new = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	new->content = (void *)content;
	if (new->content == NULL)
		new->content_size = 0;
	else
		new->content_size = content_size;
	new->next = NULL;
	return (new);
}
