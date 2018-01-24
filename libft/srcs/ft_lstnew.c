/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 23:19:40 by ashih             #+#    #+#             */
/*   Updated: 2017/12/01 17:00:59 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if ((new = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content_size != 0 && (new->content = malloc(content_size)) == NULL)
	{
		free(new);
		return (NULL);
	}
	if (content_size == 0)
		new->content = NULL;
	if (content == NULL)
	{
		if (new->content != NULL)
			free(new->content);
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
