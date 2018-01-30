# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashih <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/27 10:22:08 by ashih             #+#    #+#              #
#    Updated: 2018/01/29 19:51:36 by ashih            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libft.a

CFLAGS = -Wall -Werror -Wextra

SRC = del_and_gnl.c\
	  ft_abs.c\
	  ft_atodbl.c\
	  ft_atoi.c\
	  ft_atoi_check.c\
	  ft_bzero.c\
	  ft_char_array_del.c\
	  ft_char_array_length.c\
	  ft_exp.c\
	  ft_exp_dbl.c\
	  ft_hex_to_int_check.c\
	  ft_is_all_digits.c\
	  ft_is_prime.c\
	  ft_isalnum.c\
	  ft_isalpha.c\
	  ft_isascii.c\
	  ft_isdigit.c\
	  ft_isprint.c\
	  ft_itoa.c\
	  ft_lst_add_last.c\
	  ft_lst_at.c\
	  ft_lst_cond_remove.c\
	  ft_lst_new_ref.c\
	  ft_lst_remove_first.c\
	  ft_lst_size.c\
	  ft_lstadd.c\
	  ft_lstdel.c\
	  ft_lstdelone.c\
	  ft_lstiter.c\
	  ft_lstmap.c\
	  ft_lstnew.c\
	  ft_max.c\
	  ft_memalloc.c\
	  ft_memccpy.c\
	  ft_memchr.c\
	  ft_memcmp.c\
	  ft_memcpy.c\
	  ft_memdel.c\
	  ft_memmove.c\
	  ft_memset.c\
	  ft_min.c\
	  ft_print_bits.c\
	  ft_print_char_array.c\
	  ft_printf.c\
	  ft_printf_a.c\
	  ft_printf_a_helper.c\
	  ft_printf_any_char.c\
	  ft_printf_b.c\
	  ft_printf_big_c.c\
	  ft_printf_big_s.c\
	  ft_printf_c.c\
	  ft_printf_d.c\
	  ft_printf_d_helper.c\
	  ft_printf_e.c\
	  ft_printf_emoji.c\
	  ft_printf_f.c\
	  ft_printf_g.c\
	  ft_printf_g_helper.c\
	  ft_printf_k.c\
	  ft_printf_n.c\
	  ft_printf_o.c\
	  ft_printf_p.c\
	  ft_printf_parser.c\
	  ft_printf_r.c\
	  ft_printf_s.c\
	  ft_printf_styles.c\
	  ft_printf_u.c\
	  ft_printf_x.c\
	  ft_putchar.c\
	  ft_putchar_fd.c\
	  ft_putendl.c\
	  ft_putendl_fd.c\
	  ft_puterror.c\
	  ft_putnbr.c\
	  ft_putnbr_fd.c\
	  ft_putstr.c\
	  ft_putstr_fd.c\
	  ft_rand.c\
	  ft_round_dbl.c\
	  ft_round_ldbl.c\
	  ft_sqrt.c\
	  ft_strbisect.c\
	  ft_strcat.c\
	  ft_strchr.c\
	  ft_strclr.c\
	  ft_strcmp.c\
	  ft_strcpy.c\
	  ft_strdel.c\
	  ft_strdup.c\
	  ft_strequ.c\
	  ft_striter.c\
	  ft_striteri.c\
	  ft_strjoin.c\
	  ft_strlcat.c\
	  ft_strlen.c\
	  ft_strmap.c\
	  ft_strmapi.c\
	  ft_strncat.c\
	  ft_strnchr.c\
	  ft_strncmp.c\
	  ft_strncpy.c\
	  ft_strnequ.c\
	  ft_strnew.c\
	  ft_strnstr.c\
	  ft_strrchr.c\
	  ft_strsplit.c\
	  ft_strrev.c\
	  ft_strstr.c\
	  ft_strsub.c\
	  ft_strtrim.c\
	  ft_tolower.c\
	  ft_toupper.c\
	  get_next_line.c\
	  skip_next_line.c

OBJ = $(SRC:.c=.o)

SRCDIR = srcs/
OBJDIR = objs/

SRCS = $(addprefix $(SRCDIR), $(SRC:.c=.o))
OBJS = $(addprefix $(OBJDIR), $(OBJ))

HEADER = -I includes

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c $(CFLAGS) $(HEADER) $< -o $@

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

all: $(NAME)

clean:
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
