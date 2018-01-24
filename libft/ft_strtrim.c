/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 19:32:47 by ashih             #+#    #+#             */
/*   Updated: 2017/11/28 21:58:10 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*make_empty_str(void)
{
	char	*new;

	new = malloc(sizeof(char) * 1);
	if (new == NULL)
		return (NULL);
	new[0] = '\0';
	return (new);
}

char		*ft_strtrim(char const *s)
{
	char	*new;
	int		head;
	int		tail;
	int		i;

	if (s == NULL)
		return (NULL);
	head = 0;
	while (s[head] == ' ' || s[head] == '\t' || s[head] == '\n')
		head++;
	if (s[head] == '\0')
		return (make_empty_str());
	tail = ft_strlen(s) - 1;
	while (s[tail] == ' ' || s[tail] == '\t' || s[tail] == '\n')
		tail--;
	new = malloc(sizeof(char) * (tail - head + 2));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (head <= tail)
		new[i++] = s[head++];
	new[i] = '\0';
	return (new);
}
