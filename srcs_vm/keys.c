/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 23:24:15 by ashih             #+#    #+#             */
/*   Updated: 2018/01/26 19:50:34 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Keycode		Key				Function
** 53			ESC				Terminate program
** 124			RIGHT ARROW		Tap button to to next one cycle
** 126			UP ARROW		Hold button to fast-forward to next cycles
*/

int			key_press_hook(int keycode, t_master *m)
{
	if (keycode == 53)
		terminate(m);
	else if (keycode == 124)
		step_forward(m);
	else if (keycode == 126)
		m->forward = 1;
//---------
	if (keycode == 49)
		m->forward = m->forward ? 0 : 1;
	return (0);
}

int			key_release_hook(int keycode, t_master *m)
{
	if (keycode == 126)
		m->forward = 0;
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
