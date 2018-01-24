/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   styles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:28:14 by ashih             #+#    #+#             */
/*   Updated: 2017/12/14 14:29:31 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_style	g_styles_table[] =
{
	{"{reset}", 0},
	{"{bold}", 1},
	{"{italic}", 3},
	{"{underline}", 4},
	{"{blink}", 5},
	{"{invert}", 7},
	{"{invis}", 8},
	{"{black}", 30},
	{"{red}", 31},
	{"{green}", 32},
	{"{yellow}", 33},
	{"{blue}", 34},
	{"{magenta}", 35},
	{"{cyan}", 36},
	{"{white}", 37},
	{"{black-bg}", 40},
	{"{red-bg}", 41},
	{"{green-bg}", 42},
	{"{yellow-bg}", 43},
	{"{blue-bg}", 44},
	{"{magenta-bg}", 45},
	{"{cyan-bg}", 46},
	{"{white-bg}", 47},
	{0, 0}
};

/*
** int apply_one_style(char *format);
**
** Check if format starts with a valid style expression, e.g. "{red}",
** and print the corresponding styles code text.
**
** Return 1 if a valid style code was applied successfully.
** Return 0 otherwise.
*/

int						apply_a_style(const char **format)
{
	int					i;

	i = 0;
	while (g_styles_table[i].str)
	{
		if (ft_strnequ(g_styles_table[i].str, *format,
					ft_strlen(g_styles_table[i].str)))
		{
			ft_putstr("\x1b[");
			ft_putnbr(g_styles_table[i].code);
			ft_putchar('m');
			*format += ft_strlen(g_styles_table[i].str);
			return (1);
		}
		i++;
	}
	return (0);
}
