/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:11:03 by ashih             #+#    #+#             */
/*   Updated: 2018/01/25 01:14:38 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <ncurses.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"
# include "op_ext.h"

#define BANNER "\n\n"\
"\t   ____   U  ___ u   ____    U _____ u                      _       ____\n"\
"\tU /\"___|   \\/\"_ \\/U |  _\"\\ u \\| ___\"|/     __        __ U  /\"\\  uU |  _\"\\ u\n"\
"\t\\| | u     | | | | \\| |_) |/  |  _|\"       \\\"\\      /\"/  \\/ _ \\/  \\| |_) |/\n"\
"\t | |/__.-,_| |_| |  |  _ <    | |___       /\\ \\ /\\ / /\\  / ___ \\   |  _ <\n"\
"\t  \\____|\\_)-\\___/   |_| \\_\\   |_____|     U  \\ V  V /  U/_/   \\_\\  |_| \\_\\\n"\
"\t _// \\\\      \\\\     //   \\\\_  <<   >>     .-,_\\ /\\ /_,-. \\\\    >>  //   \\\\_\n"\
"\t(__)(__)    (__)   (__)  (__)(__) (__)     \\_)-'  '-(_/ (__)  (__)(__)  (__)\n"

#define BANNER2 "\n"\
"              _____                   _______                   _____                    _____                            _____                    _____                    _____\n"\
"             /\\    \\                 /::\\    \\                 /\\    \\                  /\\    \\                          /\\    \\                  /\\    \\                  /\\    \\\n"\
"            /::\\    \\               /::::\\    \\               /::\\    \\                /::\\    \\                        /::\\____\\                /::\\    \\                /::\\    \\\n"\
"           /::::\\    \\             /::::::\\    \\             /::::\\    \\              /::::\\    \\                      /:::/    /               /::::\\    \\              /::::\\    \\\n"\
"          /::::::\\    \\           /::::::::\\    \\           /::::::\\    \\            /::::::\\    \\                    /:::/   _/___            /::::::\\    \\            /::::::\\    \\\n"\
"         /:::/\\:::\\    \\         /:::/~~\\:::\\    \\         /:::/\\:::\\    \\          /:::/\\:::\\    \\                  /:::/   /\\    \\          /:::/\\:::\\    \\          /:::/\\:::\\    \\\n"\
"        /:::/  \\:::\\    \\       /:::/    \\:::\\    \\       /:::/__\\:::\\    \\        /:::/__\\:::\\    \\                /:::/   /::\\____\\        /:::/__\\:::\\    \\        /:::/__\\:::\\    \\\n"\
"       /:::/    \\:::\\    \\     /:::/    / \\:::\\    \\     /::::\\   \\:::\\    \\      /::::\\   \\:::\\    \\              /:::/   /:::/    /       /::::\\   \\:::\\    \\      /::::\\   \\:::\\    \\\n"\
"      /:::/    / \\:::\\    \\   /:::/____/   \\:::\\____\\   /::::::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\            /:::/   /:::/   _/___    /::::::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\\n"\
"     /:::/    /   \\:::\\    \\ |:::|    |     |:::|    | /:::/\\:::\\   \\:::\\____\\  /:::/\\:::\\   \\:::\\    \\          /:::/___/:::/   /\\    \\  /:::/\\:::\\   \\:::\\    \\  /:::/\\:::\\   \\:::\\____\\\n"\
"    /:::/____/     \\:::\\____\\|:::|____|     |:::|    |/:::/  \\:::\\   \\:::|    |/:::/__\\:::\\   \\:::\\____\\        |:::|   /:::/   /::\\____\\/:::/  \\:::\\   \\:::\\____\\/:::/  \\:::\\   \\:::|    |\n"\
"    \\:::\\    \\      \\::/    / \\:::\\    \\   /:::/    / \\::/   |::::\\  /:::|____|\\:::\\   \\:::\\   \\::/    /        |:::|__/:::/   /:::/    /\\::/    \\:::\\  /:::/    /\\::/   |::::\\  /:::|____|\n"\
"     \\:::\\    \\      \\/____/   \\:::\\    \\ /:::/    /   \\/____|:::::\\/:::/    /  \\:::\\   \\:::\\   \\/____/          \\:::\\/:::/   /:::/    /  \\/____/ \\:::\\/:::/    /  \\/____|:::::\\/:::/    /\n"\
"      \\:::\\    \\                \\:::\\    /:::/    /          |:::::::::/    /    \\:::\\   \\:::\\    \\               \\::::::/   /:::/    /            \\::::::/    /         |:::::::::/    /\n"\
"       \\:::\\    \\                \\:::\\__/:::/    /           |::|\\::::/    /      \\:::\\   \\:::\\____\\               \\::::/___/:::/    /              \\::::/    /          |::|\\::::/    /\n"\
"        \\:::\\    \\                \\::::::::/    /            |::| \\::/____/        \\:::\\   \\::/    /                \\:::\\__/:::/    /               /:::/    /           |::| \\::/____/\n"\
"         \\:::\\    \\                \\::::::/    /             |::|  ~|               \\:::\\   \\/____/                  \\::::::::/    /               /:::/    /            |::|  ~|\n"\
"          \\:::\\    \\                \\::::/    /              |::|   |                \\:::\\    \\                       \\::::::/    /               /:::/    /             |::|   |\n"\
"           \\:::\\____\\                \\::/____/               \\::|   |                 \\:::\\____\\                       \\::::/    /               /:::/    /              \\::|   |\n"\
"            \\::/    /                 ~~                      \\:|   |                  \\::/    /                        \\::/____/                \\::/    /                \\:|   |\n"\
"             \\/____/                                           \\|___|                   \\/____/                          ~~                       \\/____/                  \\|___|"


# define ERROR_USAGE "usage: vm [player1.cor] [player2.cor] [player3.cor] [player4.cor]"
# define ERROR_OPEN_FILE "No such file"
# define ERROR_CLOSE_FILE "Cannot close file"
# define ERROR_SPRITE "Sprite file not found"
# define ERROR_MEMORY "Out of memory"

# define WIN_WIDTH 1300
# define WIN_HEIGHT 1300
# define WIN_NAME "CORE WAR"

# define SQ_SIZE 3

# define RAD_TO_DEG(a)	((a) * 180.0 / M_PI)
# define DEG_TO_RAD(a)	((a) * M_PI / 180.0)

# define DEF_COLOR 0xC0C0C0
# define P1_COLOR 0x00FF00
# define P2_COLOR 0xFFFF00
# define P3_COLOR 0xFF00FF
# define P4_COLOR 0x00FFFF

# define SPRITE_00 "sprites/burger.sprite"
# define SPRITE_01 "sprites/chicken.sprite"
# define SPRITE_02 "sprites/robot.sprite"
# define SPRITE_03 "sprites/virus.sprite"


# define AFFLOG_SIZE 32

typedef struct		s_sprite
{
	int				id;
	int				width;
	int				height;
	int				*color;
	int				*alpha;
}					t_sprite;

typedef struct		s_player
{
	unsigned int	id;
	int				color;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			afflog[AFFLOG_SIZE + 1];
	unsigned int	prog_size;
	unsigned char	*prog;

	int				lives;
	int				last_lives;

	int				process_count;
	t_list			*process_list;
}					t_player;

typedef struct		s_process
{
	int				id;
	unsigned int	reg[REG_NUMBER];
	unsigned int	pc;
	int				lives;
	int				cycles;
}					t_process;

typedef struct		s_core
{
	unsigned int	value;
	int				owner; // owner = {1, 2, 3, 4}
	int				x;
	int				y;
}					t_core;

typedef struct		s_master
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*frame;
	int				bpp;
	int				size_line;
	int				endian;

	t_sprite		*sprite_table[MAX_PLAYERS];

	int				forward;

	WINDOW			*win_banner;
	WINDOW			*win_core;
	WINDOW			*win_control;
	WINDOW			*win_player[MAX_PLAYERS];

	int				current_cycle;

	int				cycle_to_die;
	int				cycle_delta;
	int				nbr_live;		// wutz dis?
	int				max_checks;		// and this?

	int				player_count;
	t_player		player[MAX_PLAYERS];

	t_core			core[MEM_SIZE];

}					t_master;

/*
** keys.c
*/
int			key_press_hook(int keycode, t_master *m);
int			key_release_hook(int keycode, t_master *m);
int			loop_hook(t_master *m);
int			terminate(t_master *m);

/*
** sprite.c
*/
int			init_sprite_table(t_master *m);
int			load_sprite(t_sprite **sprite, char *file);
int			init_sprite_dimen(t_sprite *sprite, int fd);
void		read_sprite_data(t_sprite *sprite, int fd);
void		draw_sprite(t_sprite *sprite, int x, int y, t_master *m);

/*
** read.c
*/
int			read_players(int argc, char **argv, t_master *m);
int			read_file(char *filename, t_player *p);
int			read_everything(int fd, t_player *p);
void		init_progs(t_master *m);
void		init_prog(int i, t_master *m);

/*
** draw.c - draw to minilibx window
*/
void		draw_dot(int x, int y, int color, t_master *m);
void		draw_square(int x, int y, int color, t_master *m);
void		draw_process_pc(t_master *m);

/*
** rainbow_road.c
*/
int			init_minilibx(t_master *m);
void		assign_core_pos(t_master *m);
void		init_rainbow_road(t_master *m);
void		update_rainbow_road(t_master *m);

/*
** display.c - wprintw() to ncurses windows
*/
void		puthex(unsigned char c, WINDOW *win);
void		display_process_pc(t_master *m);
void		display_core(t_master *m);
void		display_control(t_master *m);
void		display_players(t_master *m);
void		display_player(int i, t_master *m);

/*
** curses.c
*/
int			init_ncurses_stuffz(t_master *m);
int			init_windows(t_master *m);
void		update_windows(t_master *m);

/*
** main.c
*/
int			main(int argc, char **argv);
void		step_forward(t_master *m);
void		run_processes(t_master *m);
void		run_process(t_process *process);

/*
** debug.c
*/
void		print_all_players(t_master *m);
void		print_player(t_player *p);
void		print_core(t_master *m);



#endif
