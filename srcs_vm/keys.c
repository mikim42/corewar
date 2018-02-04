/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 23:24:15 by ashih             #+#    #+#             */
/*   Updated: 2018/02/03 16:42:06 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Keycode		Key				Function
** 53			ESC				Terminate program
** 124			RIGHT ARROW		Tap button to go to next one cycle
** 126			UP ARROW		Increase frame skip
** 125			DOWN ARROW		Decrease frame skip
** 49			SPACEBAR		Toggle FAST-FORWARD on/off
** 48			TAB				FAST-FORWARD until next cycle to die
*/

int			key_press_hook(int keycode, t_master *m)
{
	if (keycode == KEY_ESC)
		terminate(m);
	else if (keycode == RIGHT_ARROW)
		step_forward(m);
	else if (keycode == UP_ARROW && m->frame_skip < MAX_FRAME_SKIP)
		m->frame_skip++;
	else if (keycode == DOWN_ARROW && m->frame_skip > 0)
		m->frame_skip--;
	else if (keycode == KEY_SPACEBAR)
		m->forward = !(m->forward);
	else if (keycode == KEY_TAB)
	{
		m->stop_at_death = 1;
		m->forward = 1;
	}
	update_windows(m);
	update_rainbow_road(m);
	return (0);
}

int			loop_hook(t_master *m)
{
	if (m->forward)
		step_forward(m);
	return (0);
}

int			terminate(t_master *m)
{
	endwin();
	free_all(m);
	exit(0);
	return (0);
}
