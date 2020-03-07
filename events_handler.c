/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 18:43:22 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/07 04:33:01 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <signal.h>

int		key_pressed(int key_code, void *p)
{
	g_is_keypressed = 1;
	(void)p;
	if (key_code == EXIT_KEY)
	{
		//kill(tpid, SIGKILL);
		free_all(UNCOMPLETED);
	}
	else if (key_code == UP_ARROW)
		g_world.player.offset += 10;
	else if (key_code == DOWN_ARROW)
		g_world.player.offset -= 10;
	else if (key_code == RIGHT_ARROW)
		g_world.player.turnDirection = 1;
	else if (key_code == LEFT_ARROW)
		g_world.player.turnDirection = -1;
	else if (key_code == W_KEY)
		g_world.player.walkDirection = 1;
	else if (key_code == S_KEY)
		g_world.player.walkDirection = -1;
	//else if (key_code == W_KEY)
		
	//else if (key_code == W_KEY)
		
	return (1);
}

int		key_released(int key_code, void *p)
{
	(void)p;
	if (key_code == RIGHT_ARROW)
		g_world.player.turnDirection = 0;
	else if (key_code == LEFT_ARROW)
		g_world.player.turnDirection = 0;
	else if (key_code == W_KEY)
		g_world.player.walkDirection = 0;
	else if (key_code == S_KEY)
		g_world.player.walkDirection = 0;
	return (1);
}
