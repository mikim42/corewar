/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emoji.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:06:16 by ashih             #+#    #+#             */
/*   Updated: 2017/12/17 18:00:33 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_emoji	g_emoji_table[] =
{
	{"{neutral}", 0x1f610},
	{"{laugh-tears}", 0x1f602},
	{"{laugh-haha}", 0x1f606},
	{"{frown}", 0x1f627},
	{"{cry}", 0x1f62d},
	{"{fear}", 0x1f628},
	{"{scream}", 0x1f631},
	{"{dead}", 0x1f635},
	{"{thinking}", 0x1f914},
	{"{pray}", 0x1f64f},
	{"{toilet}", 0x1f6bd},
	{"{poop}", 0x1f4a9},
	{"{police}", 0x1f693},
	{"{rocket}", 0x1f680},
	{"{floppy}", 0x1f4be},
	{"{bomb}", 0x1f4a3},
	{"{cheese}", 0x1f9c0},
	{"{burger}", 0x1f354},
	{"{pizza}", 0x1f355},
	{"{dog}", 0x1f436},
	{"{cat}", 0x1f431},
	{"{cow}", 0x1f42e},
	{"{pig}", 0x1f437},
	{"{chicken}", 0x1f414},
	{"{turkey}", 0x1f983},
	{"{unicorn}", 0x1f984},
	{"{robot}", 0x1f916},
	{"{alien}", 0x1f47e},
	{0, 0}
};

/*
** int print_an_emoji(const char **format);
**
** Check if *format starts with a valid emoji expression, e.g. "{cheese}",
** and print the corresponding emoji unicode char.
**
** Return 1 if an emoji was found and printed successfully.
** Return 0 otherwise.
*/

int						print_an_emoji(const char **format)
{
	int					i;

	i = 0;
	while (g_emoji_table[i].str)
	{
		if (ft_strnequ(g_emoji_table[i].str, *format,
					ft_strlen(g_emoji_table[i].str)))
		{
			ft_put_wchar(g_emoji_table[i].code);
			ft_putchar(' ');
			*format += ft_strlen(g_emoji_table[i].str);
			return (1);
		}
		i++;
	}
	return (0);
}
