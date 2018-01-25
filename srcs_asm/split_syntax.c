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
	size_t	count;
	size_t	i;
	size_t	head;

	count = 0;
	i = 0;
	while (1)
	{
		while (is_space(s[i]))
			i++;
		if (!s[i])
			return (count);
		head = i;
		while (!(is_space(s[i]) || (i > head && s[i] == SEPARATOR_CHAR) || !s[i]))
		{
			i++;
			if (s[i - 1] == SEPARATOR_CHAR)
				break ;
		}
		count++;
	}
}

static void		initialize_strings(char **array, char const *s)
{
	size_t	i;
	size_t	j;
	size_t	head;

	i = 0;
	j = 0;
	while (1)
	{
		while (is_space(s[i]))
			i++;
		if (!s[i])
		{
			array[j] = 0;
			return ;
		}
		head = i;
		while (!(is_space(s[i]) || (i > head && s[i] == SEPARATOR_CHAR) || !s[i]))
		{
			i++;
			if (s[i - 1] == SEPARATOR_CHAR)
				break ;
		}
		array[j] = malloc(sizeof(char) * (i - head + 1));
		j++;
	}
}

static void		fill_array(char **array, char const *s)
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
			array[j][k] = s[i];
			k++;
			i++;
			if (s[i - 1] == SEPARATOR_CHAR)
				break ;
		}
		array[j][k] = '\0';
		j++;
	}
}

char			**split_syntax(char const *s)
{
	char	**total_array;
	size_t	t;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) == 0)
	{
		total_array = malloc(sizeof(char*) * 1);
		total_array[0] = 0;
		return (total_array);
	}
	t = count_substrings(s);
	total_array = malloc(sizeof(char*) * (t + 1));
	if (total_array == NULL)
		return (NULL);
	initialize_strings(total_array, s);
	fill_array(total_array, s);
	return (total_array);
}
