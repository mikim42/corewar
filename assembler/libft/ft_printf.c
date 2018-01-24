/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:03:29 by ashih             #+#    #+#             */
/*   Updated: 2017/12/17 03:22:25 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_for_tags(const char **format, int *chars_printed)
{
	if (apply_a_style(format))
		return (1);
	else if (print_an_emoji(format))
		return (1);
	else
	{
		ft_putchar(*(*format)++);
		(*chars_printed)++;
		return (0);
	}
}

int			parse_one_term(const char **format, va_list *args,
		int *chars_printed)
{
	int		flags[NUM_FLAGS];

	ft_bzero(flags, sizeof(flags));
	while (**format)
	{
		if (set_precision(format, args, flags))
			;
		else if (set_width(format, args, flags))
			;
		else if (set_a_double_flag(format, flags))
			;
		else if (set_a_single_flag(format, flags))
			;
		else if (do_an_ident(format, args, flags, chars_printed))
			return (1);
		else
		{
			ft_printf_any_char(*(*format)++, flags, chars_printed);
			return (0);
		}
	}
	return (-1);
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	int		chars_printed;

	va_start(args, format);
	chars_printed = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (parse_one_term(&format, &args, &chars_printed) == -1)
				return (chars_printed);
		}
		else if (*format == '{')
			check_for_tags(&format, &chars_printed);
		else
		{
			ft_putchar(*format++);
			chars_printed++;
		}
	}
	va_end(args);
	return (chars_printed);
}
