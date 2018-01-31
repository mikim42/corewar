# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/21 19:53:23 by mikim             #+#    #+#              #
#    Updated: 2018/01/30 16:45:14 by ashih            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_VM = core_io.c \
		 curses.c \
		 debug.c \
		 display_control.c \
		 display_core.c \
		 display_lives_bar.c \
		 display_players.c \
		 display_process_pc.c \
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
		 freedom.c \
		 init_progs.c \
		 keys.c \
		 main.c \
		 op_ext.c \
		 parse.c \
		 rainbow_road.c \
		 reap.c \
		 read_arg.c \
		 shuffle.c \
		 sprite.c \
		 validation.c \
		 verbose.c

SRC_ASM = assembler.c \
		  arg_parser.c \
		  check_name_comment.c \
		  init_program.c \
		  instruction_parser.c \
		  main.c \
		  op_ext.c \
		  split_syntax.c

SRC_DISASM = disassembler.c \
			 main.c \
			 op_ext.c \
			 validation.c

SRC_CHAMP = marysue.s \
			livepls.s \
			replicationcentral.s \
			doyoulikeforks.s \
			plagiarism.s \
			synchro0.s \
			synchro1.s

OBJ_VM = $(SRC_VM:.c=.o)
OBJ_ASM = $(SRC_ASM:.c=.o)
OBJ_DISASM = $(SRC_DISASM:.c=.o)
OBJ_CHAMP = $(SRC_CHAMP:.s=.cor)

SRCDIR_VM = srcs_vm/
SRCDIR_ASM = srcs_asm/
SRCDIR_DISASM = srcs_disasm/

OBJDIR_VM = objs_vm/
OBJDIR_ASM = objs_asm/
OBJDIR_DISASM = objs_disasm/

SRCDIR_CHAMP = srcs_champ/
OBJDIR_CHAMP = objs_champ/

LIBFT = libs/libft/
MLX = libs/minilibx/

SRCS_VM = $(addprefix $(SRCDIR_VM), $(SRC_VM))
OBJS_VM = $(addprefix $(OBJDIR_VM), $(OBJ_VM))

SRCS_ASM = $(addprefix $(SRCDIR_ASM), $(SRC_ASM))
OBJS_ASM = $(addprefix $(OBJDIR_ASM), $(OBJ_ASM))

SRCS_DISASM = $(addprefix $(SRCDIR_DISASM), $(SRC_DISASM))
OBJS_DISASM = $(addprefix $(OBJDIR_DISASM), $(OBJ_DISASM))

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
DISASM = disasm
CHAMP = champions

.PHONY: all $(CHAMP) clean fclean re
.SUFFIXES: .c .o .s .cor

all: $(VM) $(ASM) $(DISASM) $(CHAMP)

#COMPILING VIRTUAL MACHINE
$(OBJDIR_VM)%.o: $(SRCDIR_VM)%.c
	@/bin/mkdir -p $(OBJDIR_VM)
	@$(CC) $(CFLAG) $(WFLAG) $(VM_HEADER) $< -o $@

$(VM): $(OBJS_VM)
	@make -s -C $(LIBFT)
	@make -s -C $(MLX)
	@$(CC) $(OBJS_VM) $(VM_LIBS) -o $@
	@echo "\x1b[33;1m[$(VM) - LADIES AND GENTLEMAN, WELCOME TO THE CORE. "\
		"ARE YOU READY FOR COOOOOOOOOOREWAAAAAAR?]\x1b[0m"
	@echo

#COMPILING ASSEMBLER
$(OBJDIR_ASM)%.o: $(SRCDIR_ASM)%.c
	@/bin/mkdir -p $(OBJDIR_ASM)
	@$(CC) $(CFLAG) $(WFLAG) $(ASM_HEADER) $< -o $@

$(ASM): $(OBJS_ASM)
	@make -s -C $(LIBFT)
	@$(CC) $(OBJS_ASM) $(ASM_LIBS) -o $@
	@echo "\x1b[32;1m[$(ASM) - Partcipiants, please line up in an orderly"\
		"fashion, and I shall translate your champion source files into the"\
		"finest binaries of the land!]\x1b[0m"
	@echo

#COMPILING DISASSEMBLER
$(OBJDIR_DISASM)%.o: $(SRCDIR_DISASM)%.c
	@/bin/mkdir -p $(OBJDIR_DISASM)
	@$(CC) $(CFLAG) $(WFLAG) $(ASM_HEADER) $< -o $@

$(DISASM): $(OBJS_DISASM)
	@make -s -C $(LIBFT)
	@$(CC) $(OBJS_DISASM) $(ASM_LIBS) -o $@
	@echo "\x1b[34;1m[$(DISASM) - Bring me the corpses of your vanquished"\
		"champions, and I shall reveal the inner workings of their source"\
		"design!]\x1b[0m"
	@echo
 
#COMPILING CHAMPIONS
$(OBJDIR_CHAMP)%.cor: $(SRCDIR_CHAMP)%.s
	@/bin/mkdir -p $(OBJDIR_CHAMP)
	@echo "\x1b[32;1m[$(ASM) - Now registering champion from $(<)..."\
		"]\x1b[0m"
	@./$(ASM) $<
	@echo "\x1b[33;1mGreetings, $(notdir $(<:.s=.cor)), please proceed to"\
		"the arena at $(OBJDIR_CHAMP)\x1b[0m"
	@/bin/mv $(<:.s=.cor) $(OBJDIR_CHAMP)
	@echo

$(CHAMP): $(OBJS_CHAMP)


clean:
	@/bin/rm -rf $(OBJDIR_VM) $(OBJDIR_ASM) $(OBJDIR_DISASM)
	@make -s -C $(LIBFT) clean
	@make -s -C $(MLX) clean
	@echo "\x1b[35;1m[clean - Kicking out crowds from the last"\
		"COOOOOOOOOOREWAAAAAAR...]\x1b[0m"
	@echo

fclean: clean
	@/bin/rm -rf $(VM) $(ASM) $(DISASM) $(LIBFT)libft.a $(OBJDIR_CHAMP)
	@echo "\x1b[31;1m[fclean - Demolishing the old colosseum, so an even"\
		"fancier new one can be built for the next"\
		"COOOOOOOOOOREWAAAAAAR...]\x1b[0m"
	@echo

re: fclean all
