# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/21 19:53:23 by mikim             #+#    #+#              #
#    Updated: 2018/01/24 14:53:25 by mikim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_VM =

SRC_ASM = main.c \
		  assembler.c \
		  op_ext.c

OBJ_VM = $(SRC_VM:.c=.o)
OBJ_ASM = $(SRC_ASM:.c=.o)

SRCDIR_VM = srcs_vm/
SRCDIR_ASM = srcs_asm/

OBJDIR_VM = objs_vm/
OBJDIR_ASM = objs_asm/

CHAMPDIR = champions/
LIBDIR = libft/

SRCS_VM = $(addprefix $(SRCDIR_VM), $(SRC_VM))
OBJS_VM = $(addprefix $(OBJDIR_VM), $(OBJ_VM))

SRCS_ASM = $(addprefix $(SRCDIR_ASM), $(SRC_ASM))
OBJS_ASM = $(addprefix $(OBJDIR_ASM), $(OBJ_ASM))

LIBS = -L $(LIBDIR) -lft -lncurses
HEADER = -I includes -I $(LIBDIR)includes

CC = gcc
CFLAG = -c
WFLAG = -Wall -Wextra -Werror

VM = corewar
ASM = asm

.PHONY: all clean fclean re
.SUFFIXES: .c .o

all: $(VM) $(ASM)

#COMPILING VIRTUAL MACHINE
$(OBJDIR_VM)%.o: $(SRCDIR_VM)%.c
	@mkdir -p $(OBJDIR_VM)
	@$(CC) $(CFLAG) $(WFLAG) $(HEADER) $< -o $@

$(VM): $(OBJS_VM)
	@make -C $(LIBDIR)
	@$(CC) $(OBJS_VM) $(LIBS) -o $@
	@echo "\x1b[32;1m[$(VM) - 모래반지 빵야빵야!]\x1b[0m"


#COMPILING ASSEMBLER
$(OBJDIR_ASM)%.o: $(SRCDIR_ASM)%.c
	@mkdir -p $(OBJDIR_ASM)
	@$(CC) $(CFLAG) $(WFLAG) $(HEADER) $< -o $@

$(ASM): $(OBJS_ASM)
	@make -C $(LIBDIR)
	@$(CC) $(OBJS_ASM) $(LIBS) -o $@
	@echo "\x1b[32;1m[$(ASM) - 모래반지 빵야빵야!]\x1b[0m"

clean:
	@/bin/rm -rf $(OBJDIR_VM) $(OBJDIR_ASM)
	@make -C $(LIBDIR) clean
	@echo "\x1b[35;1m[$(VM) - clean]\x1b[0m"

fclean: clean
	@/bin/rm -f $(VM) $(ASM)
	@rm -f $(LIBDIR)libft.a
	@rm -f $(CHAMPDIR)*.cor
	@echo "\x1b[31m[$(VM) - fclean]\x1b[0m"

re: fclean all
