/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:12:54 by ashih             #+#    #+#             */
/*   Updated: 2017/12/26 00:30:33 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char *g_flags_array[] =
{
	"hh",
	"ll",
	"h",
	"l",
	"j",
	"z",
	"#",
	"0",
	"-",
	"+",
	" ",
	"L",
	"'",
	0
};

static const t_id_func		g_id_func_array[] =
{
	{'c', ft_printf_c},
	{'C', ft_printf_big_c},
	{'s', ft_printf_s},
	{'S', ft_printf_big_s},
	{'p', ft_printf_p},
	{'d', ft_printf_d},
	{'D', ft_printf_big_d},
	{'i', ft_printf_d},
	{'o', ft_printf_o},
	{'O', ft_printf_big_o},
	{'u', ft_printf_u},
	{'U', ft_printf_big_u},
	{'x', ft_printf_x},
	{'X', ft_printf_big_x},
	{'e', ft_printf_e},
	{'E', ft_printf_big_e},
	{'f', ft_printf_f},
	{'F', ft_printf_f},
	{'g', ft_printf_g},
	{'G', ft_printf_big_g},
	{'a', ft_printf_a},
	{'A', ft_printf_big_a},
	{'n', ft_printf_n},
	{'b', ft_printf_b},
	{'B', ft_printf_big_b},
	{'r', ft_printf_r},
	{'k', ft_printf_k},
	{'K', ft_printf_big_k},
	{0, 0}
};

int		set_width(const char **format, va_list *args, int *flags)
{
	int	w;

	if (**format == '*')
	{
		w = va_arg(*args, int);
		if (w < 0)
		{
			flags[i_minus] = 1;
			w = w * -1;
		}
		flags[i_width] = w;
		(*format)++;
		return (1);
	}
	if ('1' <= **format && **format <= '9')
	{
		flags[i_width] = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
		return (1);
	}
	return (0);
}

int		set_precision(const char **format, va_list *args, int *flags)
{
	if (**format != '.')
		return (0);
	flags[i_dot] = 1;
	(*format)++;
	if (**format == '*')
	{
		flags[i_precision] = va_arg(*args, int);
		if (flags[i_precision] < 0)
			flags[i_dot] = 0;
		(*format)++;
	}
	else if (ft_isdigit(**format))
	{
		flags[i_precision] = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	else
		flags[i_precision] = 0;
	return (1);
}

int		set_a_double_flag(const char **format, int *flags)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (ft_strnequ(g_flags_array[i], *format, 2))
		{
			flags[i] = 1;
			*format += 2;
			return (1);
		}
		i++;
	}
	return (0);
}

int		set_a_single_flag(const char **format, int *flags)
{
	int	i;

	i = 2;
	while (g_flags_array[i])
	{
		if (ft_strnequ(g_flags_array[i], *format, 1))
		{
			flags[i] = 1;
			*format += 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int		do_an_ident(const char **format, va_list *args, int *flags,
		int *chars_printed)
{
	int	i;

	i = 0;
	while (g_id_func_array[i].id)
	{
		if (g_id_func_array[i].id == **format)
		{
			g_id_func_array[i].func(args, flags, chars_printed);
			(*format)++;
			return (1);
		}
		i++;
	}
	return (0);
}
