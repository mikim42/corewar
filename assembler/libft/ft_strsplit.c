/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:48:47 by ashih             #+#    #+#             */
/*   Updated: 2017/11/28 19:59:25 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_substrings(char const *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (1)
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			return (count);
		while (!(s[i] == c || s[i] == '\0'))
			i++;
		count++;
	}
}

static void	initialize_strings(char **array, char const *s, char c)
{
	int		i;
	int		j;
	int		head;

	i = 0;
	j = 0;
	head = 0;
	while (1)
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
		{
			array[j] = 0;
			return ;
		}
		head = i;
		while (!(s[i] == c || s[i] == '\0'))
			i++;
		array[j] = malloc(sizeof(char) * (i - head + 1));
		j++;
	}
}

static void	fill_array(char **array, char const *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (1)
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			return ;
		k = 0;
		while (!(s[i] == c || s[i] == '\0'))
		{
			array[j][k] = s[i];
			k++;
			i++;
		}
		array[j][k] = '\0';
		j++;
	}
}

char		**ft_strsplit(char const *s, char c)
{
	char	**total_array;
	int		t;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) == 0)
	{
		total_array = malloc(sizeof(char*) * 1);
		total_array[0] = 0;
		return (total_array);
	}
	t = count_substrings(s, c);
	total_array = malloc(sizeof(char*) * (t + 1));
	if (total_array == NULL)
		return (NULL);
	initialize_strings(total_array, s, c);
	fill_array(total_array, s, c);
	return (total_array);
}
