/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:43:54 by ashih             #+#    #+#             */
/*   Updated: 2018/01/30 16:44:28 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		check_name(int flags[], char *filename)
{
	if (flags[0] == 0)
	{
		ft_printf("[!] '%s' is missing a name!\n", filename);
		return (1);
	}
	return (0);
}

int		check_comment(int flags[], char *filename)
{
	if (flags[1] == 0)
	{
		ft_printf("[!] '%s' is missing a comment!\n", filename);
		return (1);
	}
	return (0);
}
