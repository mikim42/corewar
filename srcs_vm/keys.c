/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 23:24:15 by ashih             #+#    #+#             */
/*   Updated: 2018/01/26 21:44:38 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Keycode		Key				Function
** 53			ESC				Terminate program
** 49			SPACEBAR		Turn FAST-FORWARDING on/off
** 124			RIGHT ARROW		Tap button to to next one cycle
** 126			UP ARROW		Increase frame skip
** 125			DOWN ARROW		Decrease frame skip
*/

int			key_press_hook(int keycode, t_master *m)
{
	if (keycode == 53)
		terminate(m);
	else if (keycode == 124)
		step_forward(m);
	else if (keycode == 126 && m->frame_skip < MAX_FRAME_SKIP)
	{
		m->frame_skip++;
		update_windows(m);
	}
	else if (keycode == 125 && m->frame_skip > 0)
	{
		m->frame_skip--;
		update_windows(m);
	}
	else if (keycode == 49)
	{
		m->forward = m->forward ? 0 : 1;
		update_windows(m);
		update_rainbow_road(m);
	}
	return (0);
}

int			key_release_hook(int keycode, t_master *m)
{
	(void)keycode;
	(void)m;
//	if (keycode == 126)
//		m->forward = 0;
	return (0);
}

int			loop_hook(t_master *m)
{
	if (m->forward == 1)
		step_forward(m);
	return (0);
}

int			terminate(t_master *m)
{
//	free_everything_that_is_in_our_master_struct(m);
	(void)m;
	endwin();
	exit(0);
	return (0);
}
