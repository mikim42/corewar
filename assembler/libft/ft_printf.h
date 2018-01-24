/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:02:23 by ashih             #+#    #+#             */
/*   Updated: 2017/12/26 00:35:55 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define NUM_FLAGS 16
# define BIN_STR_MAX_LEN 74
# define OCT_STR_MAX_LEN 74
# define DEC_STR_MAX_LEN 29
# define HEX_STR_MAX_LEN 19
# define PTR_HEX_STR_MAX_LEN 17
# define L_DBL_DEC_STR_MAX_LEN 100

extern const char	g_hextable_upper[];
extern const char	g_hextable_lower[];

enum			e_flags
{
	i_hh = 0,
	i_ll = 1,
	i_h = 2,
	i_l = 3,
	i_j = 4,
	i_z = 5,
	i_num_sign = 6,
	i_zero = 7,
	i_minus = 8,
	i_plus = 9,
	i_space = 10,
	i_big_l = 11,
	i_apostrophe = 12,
	i_width = 13,
	i_precision = 14,
	i_dot = 15
};

typedef void	(*t_func)(va_list *, int *, int *);

typedef struct	s_id_func
{
	char		id;
	t_func		func;
}				t_id_func;

typedef struct	s_style
{
	char		*str;
	int			code;
}				t_style;

typedef struct	s_emoji
{
	char		*str;
	wchar_t		code;
}				t_emoji;

/*
** ft_printf_n.c
*/
void			ft_printf_n(va_list *args, int *flags, int *chars_printed);

/*
** ft_printf_p.c
*/
void			ft_printf_p(va_list *args, int *flags, int *chars_printed);

/*
** ft_printf_d.c
*/
void			ft_printf_d(va_list *args, int *flags, int *chars_printed);
void			ft_printf_big_d(va_list *args, int *flags, int *chars_printed);

/*
** ft_printf_d_helper.c
*/
void			ft_printf_num_to_str(long n, char *result, int *flags);
void			ft_printf_apply_div(char *str);
void			ft_printf_d_format(char *result, int *flags, int *chars_printed,
		char *prefix);
int				ft_printf_str_prec_len(char *str, int prec_len);
void			ft_printf_putstr_prec(char *str, int prec_len);

/*
** ft_printf_u.c
*/
void			ft_printf_u(va_list *args, int *flags, int *chars_printed);
void			ft_printf_big_u(va_list *args, int *flags, int *chars_printed);
void			ft_printf_unum_to_dec_str(unsigned long n, char *result,
		int *flags);

/*
** ft_printf_o.c
*/
void			ft_printf_o(va_list *args, int *flags, int *chars_printed);
void			ft_printf_big_o(va_list *args, int *flags, int *chars_printed);
void			ft_printf_unum_to_oct_str(unsigned long n, char *result);
int				octal_prefix_hotfix(char *prefix, char *result, int *flags);

/*
** ft_printf_x.c
*/
void			ft_printf_x(va_list *args, int *flags, int *chars_printed);
void			ft_printf_big_x(va_list *args, int *flags, int *chars_printed);
void			ft_printf_unum_to_hex_str(unsigned long n, char *result,
		int *flags, int big_x);
void			ft_printf_x_format(char *result, int *flags, int *chars_printed,
		char *prefix);

/*
** ft_printf_f.c
*/
void			ft_printf_f(va_list *args, int *flags, int *chars_printed);
void			ft_printf_l_dbl_to_str(long double d, char *result, int *flags);
long double		round_at_precision(long double d, int afterpoint);

/*
** ft_printf_e.c
*/
void			ft_printf_e(va_list *args, int *flags, int *chars_printed);
void			ft_printf_big_e(va_list *args, int *flags, int *chars_printed);
void			ft_printf_l_dbl_to_sn_str(long double d, char *result,
		int *flags, int big_e);
void			put_in_scientific_notation(long double *d, int *exp);
void			float_exp_to_str(int exp, char *result, int *flags, int big_e);

/*
** ft_printf_g.c
*/
void			ft_printf_g(va_list *args, int *flags, int *chars_printed);
void			ft_printf_big_g(va_list *args, int *flags, int *chars_printed);

/*
** ft_printf_g_helper.c
*/
void			ft_printf_g_l_dbl_to_str(long double d, char *result,
		int *flags);
void			ft_printf_g_l_dbl_to_sn_str(long double d, char *result,
		int *flags, int big_e);
int				count_left_len(long double d);
int				trim_zeroes(char *result, int *flags);
void			hotfix_exp_1(char *result);

/*
** ft_printf_a.c
*/
void			ft_printf_a(va_list *args, int *flags, int *chars_printed);
void			ft_printf_big_a(va_list *args, int *flags, int *chars_printed);

/*
** ft_printf_a_helper.c
*/
void			ft_printf_l_dbl_to_hex_str(long double d, char *result,
		int *flags, int big_p);
void			ft_printf_hex_prefix_to_str(long n, char *result, int *flags,
		int big_p);
void			put_in_hex_scientific_notation(long double *d, int *exp);
void			float_hex_exp_to_str(int exp, char *result, int *flags,
		int big_e);
void			ft_printf_hex_zero_to_str(char *result, int big_p);

/*
** ft_printf_c.c
*/
void			ft_printf_c(va_list *args, int *flags, int *chars_printed);

/*
** ft_printf_big_c.c
*/
void			ft_printf_big_c(va_list *args, int *flags, int *chars_printed);
int				ft_wchar_len(wchar_t wc);
void			ft_put_wchar(wchar_t wc);

/*
** ft_printf_s.c
*/
void			ft_printf_s(va_list *args, int *flags, int *chars_printed);
void			ft_print_substr(char *str, int len, int *chars_printed);
void			ft_print_padding(int len, char c, int *chars_printed);

/*
** ft_printf_big_s.c
*/
void			ft_printf_big_s(va_list *args, int *flags, int *chars_printed);
int				ft_wstr_len(wchar_t *wstr);
int				ft_print_subwstr_char_count(wchar_t *wstr, int char_len);
void			ft_print_subwstr(wchar_t *wstr, int char_len,
		int *chars_printed);

/*
** ft_printf_any_char.c
*/
void			ft_printf_any_char(char c, int *flags,
		int *chars_printed);

/*
** ft_printf_b.c
*/
void			ft_printf_b(va_list *args, int *flags, int *chars_printed);
void			ft_printf_big_b(va_list *args, int *flags, int *chars_printed);
void			ft_printf_unum_to_bin_str(unsigned long n, char *result,
		int *flags);

/*
** ft_printf_r.c
*/
void			ft_printf_r(va_list *args, int *flags, int *chars_printed);
void			ft_print_substr_r(char *str, int len, int *chars_printed);

/*
** ft_printf_k.c
*/
void			ft_printf_k(va_list *args, int *flags, int *chars_printed);
void			ft_printf_big_k(va_list *args, int *flags, int *chars_printed);
void			ft_print_substr_k(char *str, int len, int *chars_printed,
		int big_k);

/*
** ft_printf_broke.c
*/
void			ft_printf_big_c_broke(va_list *args, int *flags,
		int *chars_printed);
void			ft_printf_big_s_broke(va_list *args, int *flags,
		int *chars_printed);
int				ft_wstr_len_broke(wchar_t *wstr);
void			ft_print_subwstr_broke(wchar_t *wstr, int len,
		int *chars_printed);

/*
** styles.c
*/
int				apply_a_style(const char **format);

/*
** emoji.c
*/
int				print_an_emoji(const char **format);

/*
** parser.c
*/
int				set_width(const char **format, va_list *args, int *flags);
int				set_precision(const char **format, va_list *args, int *flags);
int				set_a_double_flag(const char **format, int *flags);
int				set_a_single_flag(const char **format, int *flags);
int				do_an_ident(const char **format, va_list *args, int *flags,
		int *chars_printed);

/*
** ft_printf.c
*/
int				check_for_tags(const char **format, int *chars_printed);
int				parse_one_term(const char **format, va_list *args,
		int *chars_printed);
int				ft_printf(const char *format, ...);

#endif
