/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:11:03 by ashih             #+#    #+#             */
/*   Updated: 2018/01/29 16:41:32 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <ncurses.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"
# include "op_ext.h"

#define BANNER2 \
"              _____                   _______                   _____    "\
"                _____                            _____            "\
"        _____                    _____\n"\
"             /\\    \\                 /::\\    \\                 /\\   "\
" \\                  /\\    \\                          /\\    \\ "\
"                 /\\    \\                  /\\    \\\n"\
"            /::\\    \\               /::::\\    \\               /::\\  "\
"  \\                /::\\    \\                        /::\\____\\"\
"                /::\\    \\                /::\\    \\\n"\
"           /::::\\    \\             /::::::\\    \\             /::::\\ "\
"   \\              /::::\\    \\                      /:::/    /  "\
"             /::::\\    \\              /::::\\    \\\n"\
"          /::::::\\    \\           /::::::::\\    \\           /::::::\\"\
"    \\            /::::::\\    \\                    /:::/   _/___"\
"            /::::::\\    \\            /::::::\\    \\\n"\
"         /:::/\\:::\\    \\         /:::/~~\\:::\\    \\         /:::/\\:"\
"::\\    \\          /:::/\\:::\\    \\                  /:::/   /\\"\
"    \\          /:::/\\:::\\    \\          /:::/\\:::\\    \\\n"\
"        /:::/  \\:::\\    \\       /:::/    \\:::\\    \\       /:::/__\\"\
":::\\    \\        /:::/__\\:::\\    \\                /:::/   /::"\
"\\____\\        /:::/__\\:::\\    \\        /:::/__\\:::\\    \\\n"\
"       /:::/    \\:::\\    \\     /:::/    / \\:::\\    \\     /::::\\   "\
"\\:::\\    \\      /::::\\   \\:::\\    \\              /:::/   /:"\
"::/    /       /::::\\   \\:::\\    \\      /::::\\   \\:::\\    \\\n"\
"      /:::/    / \\:::\\    \\   /:::/____/   \\:::\\____\\   /::::::\\  "\
" \\:::\\    \\    /::::::\\   \\:::\\    \\            /:::/   /::"\
":/   _/___    /::::::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\\n"\
"     /:::/    /   \\:::\\    \\ |:::|    |     |:::|    | /:::/\\:::\\   "\
"\\:::\\____\\  /:::/\\:::\\   \\:::\\    \\          /:::/___/:::/"\
"   /\\    \\  /:::/\\:::\\   \\:::\\    \\  /:::/\\:::\\   \\:::\\____\\\n"\
"    /:::/____/     \\:::\\____\\|:::|____|     |:::|    |/:::/  \\:::\\  "\
" \\:::|    |/:::/__\\:::\\   \\:::\\____\\        |:::|   /:::/   "\
"/::\\____\\/:::/  \\:::\\   \\:::\\____\\/:::/  \\:::\\   \\:::|    |\n"\
"    \\:::\\    \\      \\::/    / \\:::\\    \\   /:::/    / \\::/   |:::"\
":\\  /:::|____|\\:::\\   \\:::\\   \\::/    /        |:::|__/:::/ "\
"  /:::/    /\\::/    \\:::\\  /:::/    /\\::/   |::::\\  /:::|____|\n"\
"     \\:::\\    \\      \\/____/   \\:::\\    \\ /:::/    /   \\/____|:::"\
"::\\/:::/    /  \\:::\\   \\:::\\   \\/____/          \\:::\\/:::/"\
"   /:::/    /  \\/____/ \\:::\\/:::/    /  \\/____|:::::\\/:::/    /\n"\
"      \\:::\\    \\                \\:::\\    /:::/    /          |::::::"\
":::/    /    \\:::\\   \\:::\\    \\               \\::::::/   /::"\
":/    /            \\::::::/    /         |:::::::::/    /\n"\
"       \\:::\\    \\                \\:::\\__/:::/    /           |::|\\:"\
":::/    /      \\:::\\   \\:::\\____\\               \\::::/___/::"\
":/    /              \\::::/    /          |::|\\::::/    /\n"\
"        \\:::\\    \\                \\::::::::/    /            |::| \\:"\
":/____/        \\:::\\   \\::/    /                \\:::\\__/:::/ "\
"   /               /:::/    /           |::| \\::/____/\n"\
"         \\:::\\    \\                \\::::::/    /             |::|  ~|"\
"               \\:::\\   \\/____/                  \\::::::::/    "\
"/               /:::/    /            |::|  ~|\n"\
"          \\:::\\    \\                \\::::/    /              |::|   |"\
"                \\:::\\    \\                       \\::::::/    /"\
"               /:::/    /             |::|   |\n"\
"           \\:::\\____\\                \\::/____/               \\::|   "\
"|                 \\:::\\____\\                       \\::::/    /"\
"               /:::/    /              \\::|   |\n"\
"            \\::/    /                 ~~                      \\:|   |  "\
"                \\::/    /                        \\::/____/      "\
"          \\::/    /                \\:|   |\n"\
"             \\/____/                                           \\|___|  "\
"                 \\/____/                          ~~             "\
"          \\/____/                  \\|___|"

/*
** Error Messages
*/
# define ERROR_USAGE			"usage: corewar [-e] [-dump nbr_cycle] "\
"[[-n number] champion1.cor] ..."
# define ERROR_OPEN_FILE		"No such file"
# define ERROR_CLOSE_FILE		"Cannot close file"
# define ERROR_SPRITE			"Sprite file not found"
# define ERROR_MEMORY			"Out of memory"
# define ERROR_HEADER			"Invalid header"
# define ERROR_FORMAT			"Invalid format"
# define ERROR_CHAMP_SIZE		"Champion program size is too large"
# define ERROR_MANY_PLAYERS		"Too many champions (maximum of 4 allowed)"
# define ERROR_FEW_PLAYERS		"Need at least one champion"
# define UNSET_VALUE			(-42)

/*
** Minilibx
*/
# define WIN_WIDTH				1300
# define WIN_HEIGHT				1300
# define WIN_NAME				"CORE WAR"

# define KEY_ESC				53
# define KEY_SPACEBAR			49
# define KEY_TAB				48
# define RIGHT_ARROW			124
# define UP_ARROW				126
# define DOWN_ARROW				125

# define SQ_SIZE				3
# define BIG_SQ_SIZE			7
# define HUGE_SQ_SIZE			600

# define DEF_COLOR				0xC0C0C0
# define P1_COLOR				0x00FF00
# define P2_COLOR				0xFFFF00
# define P3_COLOR				0xFF00FF
# define P4_COLOR				0x00FFFF

# define SPRITE_00				"sprites/burger.sprite"
# define SPRITE_01				"sprites/chicken.sprite"
# define SPRITE_02				"sprites/robot.sprite"
# define SPRITE_03				"sprites/virus.sprite"
# define SPRITE_X				"sprites/red-x.sprite"

# define SPRITE_LARGE_00		"sprites/burger_large.sprite"
# define SPRITE_LARGE_01		"sprites/chicken_large.sprite"
# define SPRITE_LARGE_02		"sprites/robot_large.sprite"
# define SPRITE_LARGE_03		"sprites/virus_large.sprite"

/*
** Display-related
*/
# define MAX_FRAME_SKIP			100
# define LIFEBAR_WIDTH			42
# define DEATH_LEN				42
# define AFFLOG_SIZE			(45 * 3)

/*
** Mechanic-related
*/
# define P1_ID					0xFFFFFFFF

typedef struct					s_color
{
	int							rgb;
	int							alpha;
}								t_color;

typedef struct					s_sprite
{
	int							width;
	int							height;
	t_color						color[];
}								t_sprite;

typedef struct					s_player
{
	unsigned int				id;
	int							n_flag_pos;
	int							color;
	char						name[PROG_NAME_LENGTH + 1];
	char						comment[COMMENT_LENGTH + 1];
	char						afflog[AFFLOG_SIZE + 1];
	unsigned int				prog_size;
	unsigned char				*prog;

	int							lives;
	int							last_lives;
	int							cycle_last_live;

	int							process_count;
	void						*master;
}								t_player;

typedef struct					s_process
{
	t_player					*player;
	int							reg[REG_NUMBER];
	unsigned int				pc;
	unsigned int				lives;
	unsigned char				opcode;
	int							cycles;
	int							carry;
}								t_process;

typedef struct					s_core
{
	unsigned int				value;
	int							owner;
	int							x;
	int							y;
	int							death;
	int							dier;
}								t_core;

typedef struct					s_master
{
	void						*mlx;
	void						*win;
	void						*img;
	char						*frame;
	int							bpp;
	int							size_line;
	int							endian;
	t_sprite					*sprite_table[MAX_PLAYERS];
	t_sprite					*sprite_large_table[MAX_PLAYERS];
	t_sprite					*sprite_x_table[MAX_PLAYERS];

	WINDOW						*win_banner;
	WINDOW						*win_core;
	WINDOW						*win_control;
	WINDOW						*win_player[MAX_PLAYERS];
	WINDOW						*win_extra;

	int							forward;
	int							stop_at_death;
	int							frame_skip;
	int							fs_counter;

	int							current_cycle;
	int							cycle_to_die;
	int							ctd_counter;
	unsigned int				nbr_lives;
	int							checks;

	int							player_count;
	t_player					player[MAX_PLAYERS];

	t_core						core[MEM_SIZE];
	t_list						*process_list;

	t_player					*winner;
	int							show_winner;

	int							v_flag;
	int							e_flag;
	int							d_flag;
	int							n_flag;
	int							open_spot;
}								t_master;

/*
** keys.c
*/
int								key_press_hook(int keycode, t_master *m);
int								loop_hook(t_master *m);
int								terminate(t_master *m);

/*
** sprite.c
*/
int								init_sprite_x_table(t_master *m);
int								init_sprite_table(t_master *m);
int								load_sprite(t_sprite **sprite, char *file);
void							draw_sprite(t_sprite *sprite, int x, int y,
											t_master *m);
/*
** shuffle.c
*/
void							shuffle_players(t_master *m);
void							shuffle_players_part_two(t_player array[],
											t_master *m);
int								empty_pos(t_player array[], int i, t_master *m);

/*
** parse.c
*/
int								parse_args(int argc, char **argv, t_master *m);
int								parse_arg(int argc, int *i, char **argv,
											t_master *m);
int								read_player(char *argv, t_master *m);
int								read_file(char *filename, t_player *p);
int								read_everything(int fd, t_player *p);

/*
** init_progs.c
*/
void							init_progs(t_master *m);
void							init_prog(int i, t_master *m);

/*
** draw.c -	draw to minilibx window
*/
void							draw_dot(int x, int y, int color, t_master *m);
void							draw_square(int x, int y, int color,
											t_master *m);
void							draw_big_square(int x, int y, int color,
											t_master *m);
void							draw_huge_square(int x, int y, int color,
											t_master *m);
void							draw_process_pc(t_master *m);

/*
** rainbow_road.c
*/
int								init_minilibx(t_master *m);
void							assign_core_pos(t_master *m);
int								init_rainbow_road(t_master *m);
void							update_rainbow_road(t_master *m);
void							draw_winner(t_master *m);

/*
** display_core.c
*/
void							display_core(t_master *m);
void							put_hex(unsigned char c, WINDOW *win);

/*
** display_process_pc.c
*/
void							display_process_pc(t_master *m);
void							find_lives(t_master *m);
void							highlight_pid(t_process *process, t_master *m);
int								whose_pid(t_process *process, t_master *m);

/*
** display_control.c
*/
void							display_control(t_master *m);
int								total_processes(t_master *m);
void							display_winner(t_master *m);

/*
** display_lives_bar.c
*/
void							display_lives_bar(t_master *m);
int								total_lives(t_master *m);
void							display_last_lives_bar(t_master *m);
int								total_last_lives(t_master *m);

/*
** display_players.c
*/
void							display_players(t_master *m);
void							display_player(int i, t_master *m);

/*
** curses.c
*/
int								init_ncurses_stuffz(t_master *m);
int								init_windows(t_master *m);
void							update_windows(t_master *m);

/*
** main.c
*/
unsigned int					ft_rand(void);
void							verbose_intro(t_master *m);
void							verbose_outro(t_master *m);
int								main(int argc, char **argv);
void							build_last_cycle(t_master *m);
void							step_forward(t_master *m);
void							run_processes(t_master *m);
void							run_process(t_process *process, t_master *m);

/*
** reap.c
*/
void							reap_processes(t_master *m);
int								process_should_die(void *process, size_t size);
void							del_process(void *process, size_t size);

/*
** core_io.c
*/
short							read_short(t_master *m, unsigned int offset);
int								read_int(t_master *m, unsigned int offset);
void							write_int(t_process *process, t_master *m,
											unsigned int offset, int value);

/*
** read_arg.c
*/
int								read_reg_exact(t_process *process, t_master *m,
											unsigned int arg);
int								read_ind_exact(t_process *process, t_master *m,
											unsigned int arg);
int								read_arg(t_process *process, t_master *m,
											unsigned int arg);
int								read_larg(t_process *process, t_master *m,
											unsigned int arg);

/*
** validation.c
*/
size_t							count_bytes(unsigned char arg_code,
											int short_dir);
int								is_valid_reg(unsigned char reg_num);
unsigned char					get_type(t_process *process, t_master *m,
											unsigned int i);
int								validate_args(t_process *process, t_master *m);
size_t							instruction_length(t_process *process,
											t_master *m);

/*
** do_live.c
*/
void							do_live(t_process *process, t_master *m);

/*
** do_ld.c
*/
void							do_ld(t_process *process, t_master *m);

/*
** do_st.c
*/
void							do_st(t_process *process, t_master *m);

/*
** do_add.c
*/
void							do_add(t_process *process, t_master *m);

/*
** do_sub.c
*/
void							do_sub(t_process *process, t_master *m);

/*
** do_and.c
*/
void							do_and(t_process *process, t_master *m);

/*
** do_or.c
*/
void							do_or(t_process *process, t_master *m);

/*
** do_xor.c
*/
void							do_xor(t_process *process, t_master *m);

/*
** do_zjmp.c
*/
void							do_zjmp(t_process *process, t_master *m);

/*
** do_ldi.c
*/
void							do_ldi(t_process *process, t_master *m);

/*
** do_sti.c
*/
void							do_sti(t_process *process, t_master *m);

/*
** do_fork.c
*/
void							do_fork(t_process *process, t_master *m);

/*
** do_lld.c
*/
void							do_lld(t_process *process, t_master *m);

/*
** do_lldi.c
*/
void							do_lldi(t_process *process, t_master *m);

/*
** do_lfork.c
*/
void							do_lfork(t_process *process, t_master *m);

/*
** do_aff.c
*/
void							do_aff(t_process *process, t_master *m);
void							append_afflog(unsigned int reg_num,
											t_process *process);
/*
** debug.c
*/
void							print_all_players(t_master *m);
void							print_player(t_player *p);
void							print_core(t_master *m);

#endif
