/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 16:37:26 by ashih             #+#    #+#             */
/*   Updated: 2017/12/26 00:35:49 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_num_to_str(long n, char *result, int *flags)
{
	int		i;
	int		sign;

	i = 0;
	sign = (n < 0) ? -1 : 1;
	if (n == 0)
		result[i++] = '0';
	else
		while (n != 0)
		{
			result[i++] = n % 10 * sign + '0';
			n = n / 10;
		}
	if (sign == -1)
		result[i++] = '-';
	else if (flags[i_plus] == 1)
		result[i++] = '+';
	else if (flags[i_space] == 1)
		result[i++] = ' ';
	result[i] = '\0';
	ft_strrev(result);
	if (flags[i_apostrophe] == 1)
		ft_printf_apply_div(result);
}

void		ft_printf_apply_div(char *str)
{
	char	temp[L_DBL_DEC_STR_MAX_LEN];
	int		offset;
	int		i;
	int		j;

	offset = ft_strlen(str) % 3;
	i = 0;
	j = 0;
	if (*str == ' ' || *str == '+' || *str == '-')
		temp[j++] = str[i++];
	while (str[i])
	{
		if (i != 0 && (i - offset) % 3 == 0 && '0' <= str[i - 1] &&
				str[i - 1] <= '9')
			temp[j++] = ',';
		temp[j++] = str[i++];
	}
	temp[j] = '\0';
	ft_strcpy(str, temp);
}

void		ft_printf_d_format(char *result, int *flags, int *chars_printed,
		char *prefix)
{
	int		print_len;
	char	pad_char;

	pad_char = (flags[i_zero] && !flags[i_minus] && !flags[i_dot]) ? '0' : ' ';
	print_len = ft_strlen(prefix);
	print_len += (flags[i_dot]) ? ft_printf_str_prec_len(result,
			flags[i_precision]) : ft_strlen(result);
	flags[i_zero] ? ft_putstr(prefix) : 0;
	if (flags[i_minus] == 0 && flags[i_width] > print_len)
		ft_print_padding(flags[i_width] - print_len, pad_char, chars_printed);
	!flags[i_zero] ? ft_putstr(prefix) : 0;
	(flags[i_dot]) ? ft_printf_putstr_prec(result, flags[i_precision]) :
		ft_putstr(result);
	*chars_printed += print_len;
	if (flags[i_minus] == 1 && flags[i_width] > print_len)
		ft_print_padding(flags[i_width] - print_len, pad_char, chars_printed);
}

int			ft_printf_str_prec_len(char *str, int prec_len)
{
	int		len;

	len = 0;
	if (*str == ' ' || *str == '+' || *str == '-')
	{
		len++;
		str++;
	}
	if (ft_strequ(str, "0") && prec_len == 0)
		return (len);
	len += ft_max((int)ft_strlen(str), prec_len);
	return (len);
}

void		ft_printf_putstr_prec(char *str, int prec_len)
{
	int		i;

	if (*str == ' ' || *str == '+' || *str == '-')
	{
		ft_putchar(*str);
		str++;
	}
	if (ft_strequ(str, "0") && prec_len == 0)
		return ;
	i = 0;
	while (i < prec_len - (int)ft_strlen(str))
	{
		ft_putchar('0');
		i++;
	}
	ft_putstr(str);
}
