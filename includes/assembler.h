/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:09:54 by apuel             #+#    #+#             */
/*   Updated: 2018/01/30 22:11:32 by Mingyun K        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

# include "libft.h"
# include "op_ext.h"

# define UNKNOWN_ARG 	"Unknown argument; '%s'!"
# define NOT_ENOUGH_ARG	"Not enough arguments for %s!"
# define TOO_MANY_ARG	"Too many arguments for %s!"

# define INVALID_ERR	"Invalid '%s'!"
# define EOF_ERR		"'%s' reaches EOF!"

# define INVALID_REG	"Invalid type 'REG' for %s, argument %lu!"
# define BAD_REG		"Bad 'REG' value, '%s'!"

# define INVALID_LABEL	"Invalid label, '%s'!"
# define DUP_LABEL		"Duplicate label, '%s'!"
# define UNDEF_LABEL	"Undefined label, '%s'!"

# define INVALID_DIR	"Invalid type 'DIRECT' for '%s', argument %lu!"
# define BAD_DIRECT		"Bad 'DIRECT' value, '%s'!"

# define INVALID_INST	"Invalid instruction '%s'!"
# define FILE_ABRUPT	"File ended abruptly!"

# define ALLOC_FAIL		"Failed to allocate memory!"

typedef struct			s_asm_ctx
{
	unsigned char		code[0x10];
	size_t				pc;
	int					op;
	size_t				arg;
	t_list				*labels;
}						t_asm_ctx;

/*
**						main.c
*/

long					throw_error(char *string, long result);
long					throw_verr(char *format, long f0, long f1, long f2);
void					create_binary(t_program *program,
										char *name, size_t size);
char					*ft_readfile(char *path);

/*
**						check_name_comment.c
*/

int						check_name(int flags[], char *filename);
int						check_comment(int flags[], char *filename);

/*
**						assembler.c
*/

long					preprocess(char *source, char *ref,
										char *dst, size_t size);
char					**parse_source(char *source, t_program *program,
										int flags[]);
void					assemble_program(char **assembly, t_program **program);
t_program				*the_assemble_everything_function(char *source,
															int flags[]);

/*
**						arg_parser.c
*/

long					label_arg(char *argument, t_program *program,
										t_list *labels, int *result);
long					dir_ext(char *argument, t_asm_ctx *ctx,
										t_program *program, t_list *labels);
long					dir_arg(char *argument, t_asm_ctx *ctx,
										t_program *program, t_list *labels);
long					ind_ext(char *argument, t_asm_ctx *ctx,
										t_program *program, t_list *labels);
long					ind_arg(char *argument, t_asm_ctx *ctx,
										t_program *program, t_list *labels);

/*
**						init_program.c
*/

int						is_valid_label(char *label);
t_list					*create_label(char **assembly, t_list **labels,
										size_t i, size_t pc);
t_list					*create_label(char **assembly, t_list **labels,
										size_t i, size_t pc);
t_program				*init_program(char **assembly, t_program *program,
										t_list **labels, size_t pc);

/*
**						instruction_parser.c
*/

void					write_byteswapped(void *dst, void *src, size_t n);
long					reg_arg(char *argument, t_asm_ctx *ctx);
long					check_arg(char *assem, t_asm_ctx *ctx,
										t_program *program, t_list *labels);
long					assemble_instruction(char **assembly, size_t *i,
										t_asm_ctx *ctx, t_program *program);
long					assemble(char **assembly, size_t *i,
										t_program *program, t_list *labels);

/*
**						split_syntax.c
*/

char					**split_syntax(const char *str);

#endif
