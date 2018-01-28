/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:07:15 by ashih             #+#    #+#             */
/*   Updated: 2018/01/28 01:18:40 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
** Part 1 - Libc Functions
*/
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *isrc, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *little,
		size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

/*
** Part 2 - Additional Functions
*/
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
** Bonus - Linked List Functions
*/
typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** Bonus - My Additional Functions
*/
int					ft_min(int a, int b);
int					ft_max(int a, int b);
int					ft_abs(int a);
int					ft_exp(int base, unsigned int power);
int					ft_sqrt(int n);
int					ft_is_prime(int n);
int					ft_char_array_length(char **array);
void				ft_print_bits(unsigned char octet);
t_list				*ft_lst_new_ref(void const *content, size_t content_size);
int					ft_lst_size(t_list *lst);
void				ft_lst_add_last(t_list **alst, t_list *new);
void				*ft_lst_remove_first(t_list **alst);
void				ft_strrev(char *str);
long				ft_round_ldbl(long double d);
void				*ft_lst_at(t_list *alst, unsigned int n);
int					ft_atoi_check(char *str, int *n);
int					ft_hex_to_int_check(char *str, int *n);
int					ft_round_dbl(double d);
void				ft_print_char_array(char **array);
int					ft_puterror(char *message, int ret);
void				ft_char_array_del(char **array);
void				skip_next_line(int fd, int n);
int					ft_is_all_digits(char *str);
char				*ft_strnchr(char *str, int c, int n);
int					ft_strbisect(char *str, char *mid, char **new1,
		char **new2);
double				ft_exp_dbl(int base, unsigned int power);
double				ft_atodbl(const char *str);
void				del_and_gnl(int fd, char **line);
void				ft_lst_cond_remove(t_list **list,
	int (*cond)(void *, size_t), void (*del)(void *, size_t));

/*
** get_next_line.c
*/
typedef struct		s_gnl
{
	int				fd;
	char			*str;
}					t_gnl;

int					get_next_line(const int fd, char **line);

/*
** ft_printf.c
*/
int					ft_printf(const char *format, ...);

#endif
