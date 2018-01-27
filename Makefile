# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/21 19:53:23 by mikim             #+#    #+#              #
#    Updated: 2018/01/27 03:17:26 by ashih            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_VM = curses.c \
		 debug.c \
		 display.c \
		 do_live.c \
		 do_ld.c \
		 do_st.c \
		 do_add.c \
		 do_sub.c \
		 do_and.c \
		 do_or.c \
		 do_xor.c \
		 do_zjmp.c \
		 do_ldi.c \
		 do_sti.c \
		 do_fork.c \
		 do_lld.c \
		 do_lldi.c \
		 do_lfork.c \
		 do_aff.c \
		 draw.c \
		 keys.c \
		 functions.c \
		 functions_two.c \
		 functions_three.c \
		 main.c \
		 op_ext.c \
		 rainbow_road.c \
		 read.c \
		 sprite.c

SRC_ASM = main.c \
		  assembler.c \
		  assembler_two.c \
		  assembler_three.c \
		  assembler_four.c \
		  split_syntax.c \
		  op_ext.c

SRC_CHAMP = marysue.s \
			livepls.s \
			replicationcentral.s \
			doyoulikeforks.s \
			plagiarism.s

OBJ_VM = $(SRC_VM:.c=.o)
OBJ_ASM = $(SRC_ASM:.c=.o)
OBJ_CHAMP = $(SRC_CHAMP:.s=.cor)

SRCDIR_VM = srcs_vm/
SRCDIR_ASM = srcs_asm/

OBJDIR_VM = objs_vm/
OBJDIR_ASM = objs_asm/

SRCDIR_CHAMP = srcs_champ/
OBJDIR_CHAMP = objs_champ/

LIBFT = libs/libft/
MLX = libs/minilibx/

SRCS_VM = $(addprefix $(SRCDIR_VM), $(SRC_VM))
OBJS_VM = $(addprefix $(OBJDIR_VM), $(OBJ_VM))

SRCS_ASM = $(addprefix $(SRCDIR_ASM), $(SRC_ASM))
OBJS_ASM = $(addprefix $(OBJDIR_ASM), $(OBJ_ASM))

SRCS_CHAMP = $(addprefix $(SRCDIR_CHAMP), $(SRC_CHAMP))
OBJS_CHAMP = $(addprefix $(OBJDIR_CHAMP), $(OBJ_CHAMP))

VM_LIBS = -L $(LIBFT) -lft -L $(MLX) -lmlx -lncurses \
		  -framework OpenGL -framework AppKit

ASM_LIBS = -L $(LIBFT) -lft

VM_HEADER = -I includes -I $(LIBFT)includes -I $(MLX)
ASM_HEADER = -I includes -I $(LIBFT)includes

CC = gcc
CFLAG = -c
WFLAG = -Wall -Wextra -Werror

VM = corewar
ASM = asm
CHAMP = champions

.PHONY: all $(CHAMP) clean fclean re
.SUFFIXES: .c .o .s .cor

all: $(VM) $(ASM) $(CHAMP)

#COMPILING VIRTUAL MACHINE
$(OBJDIR_VM)%.o: $(SRCDIR_VM)%.c
	@/bin/mkdir -p $(OBJDIR_VM)
	@$(CC) $(CFLAG) $(WFLAG) $(VM_HEADER) $< -o $@

$(VM): $(OBJS_VM)
	@make -s -C $(LIBFT)
	@make -s -C $(MLX)
	@$(CC) $(OBJS_VM) $(VM_LIBS) -o $@
	@echo "\x1b[32;1m[$(VM) - 모래반지 빵야빵야!]\x1b[0m"


#COMPILING ASSEMBLER
$(OBJDIR_ASM)%.o: $(SRCDIR_ASM)%.c
	@/bin/mkdir -p $(OBJDIR_ASM)
	@$(CC) $(CFLAG) $(WFLAG) $(ASM_HEADER) $< -o $@

$(ASM): $(OBJS_ASM)
	@make -s -C $(LIBFT)
	@$(CC) $(OBJS_ASM) $(ASM_LIBS) -o $@
	@echo "\x1b[32;1m[$(ASM) - 모래반지 빵야빵야!]\x1b[0m"

 
#COMPILING CHAMPIONS
$(OBJDIR_CHAMP)%.cor: $(SRCDIR_CHAMP)%.s
	@/bin/mkdir -p $(OBJDIR_CHAMP)
	@./$(ASM) $<
	@/bin/mv $(<:.s=.cor) $(OBJDIR_CHAMP)
	@echo "\x1b[32;1m[$(notdir $(<:.s=)) has joined the LEAGUE!]\x1b[0m"

$(CHAMP): $(OBJS_CHAMP)


clean:
	@/bin/rm -rf $(OBJDIR_VM) $(OBJDIR_ASM)
	@make -s -C $(LIBFT) clean
	@make -s -C $(MLX) clean
	@echo "\x1b[35;1m[$(VM) - clean]\x1b[0m"

fclean: clean
	@/bin/rm -rf $(VM) $(ASM) $(LIBFT)libft.a $(OBJDIR_CHAMP)
	@echo "\x1b[31;1m[$(VM) - fclean]\x1b[0m"

re: fclean all
