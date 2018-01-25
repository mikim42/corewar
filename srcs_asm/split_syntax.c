/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:48:47 by ashih             #+#    #+#             */
/*   Updated: 2017/11/28 19:59:25 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static int		is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static size_t	count_substrings(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (1)
	{
		while (is_space(s[i]))
			i++;
		if (!s[i])
			return (j);
		k = i;
		while (!(is_space(s[i]) || (i > k && s[i] == SEPARATOR_CHAR) || !s[i]))
			if (s[++i - 1] == SEPARATOR_CHAR)
				break ;
		j++;
	}
}

static int		initialize_substrings(char **substrings, char const *s)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (1)
	{
		while (is_space(s[i]))
			i++;
		if (!s[i])
			return (1);
		k = i;
		while (!(is_space(s[i]) || (i > k && s[i] == SEPARATOR_CHAR) || !s[i]))
			if (s[++i - 1] == SEPARATOR_CHAR)
				break ;
		if (!(substrings[j++] = ft_memalloc(sizeof(char) * (i - k + 1))))
		{
			i = 0;
			while (substrings[i])
				free(substrings[i++]);
			free(substrings);
			return (0);
		}
	}
}

static void		copy_substrings(char **substrings, char const *s)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (1)
	{
		while (is_space(s[i]))
			i++;
		if (!s[i])
			return ;
		k = 0;
		while (!(is_space(s[i]) || (k && s[i] == SEPARATOR_CHAR) || !s[i]))
		{
			substrings[j][k++] = s[i++];
			if (s[i - 1] == SEPARATOR_CHAR)
				break ;
		}
		substrings[j++][k] = '\0';
	}
}

char			**split_syntax(char const *s)
{
	char	**substrings;
	size_t	count;

	if (!s)
		return (0);
	if (!ft_strlen(s))
	{
		substrings = ft_memalloc(sizeof(char *) * 1);
		return (substrings);
	}
	count = count_substrings(s);
	if ((substrings = ft_memalloc(sizeof(char *) * (count + 1))))
	{
		if (initialize_substrings(substrings, s))
			copy_substrings(substrings, s);
	}
	return (substrings);
}
