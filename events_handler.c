/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 18:43:22 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/10 03:19:36 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <signal.h>

void	jump()
{
	int i = -1;
	while (++i < 200)
		g_world.player.height += 1;
}

int		key_pressed(int key_code, void *p)
{
	g_is_keypressed = 1;
	(void)p;
	if (key_code == CTRL_KEY)
	{
		int i = -1;
		while (++i < g_world.numofsprites)
			if (g_world.sprites[i].is_static == 1)
			{
				g_world.sprites[i].anim.is_running = 1;
				break;
			}
	}
	else if (key_code == EXIT_KEY)
	{
		kill(pid, SIGKILL);
		free_all(UNCOMPLETED);
	}
	else if (key_code == UP_ARROW)
	{
		if (g_world.player.offset >= 0 && g_world.player.offset < SHEIGHT)
			g_world.player.offset += 30;
	}
	else if (key_code == DOWN_ARROW)
	{
		if (g_world.player.offset >= 0 && g_world.player.offset < SHEIGHT)
			g_world.player.offset -= 30;
	}//else if (key_code == SPACE_KEY)
	//	jump();
	else if (key_code == RIGHT_ARROW)
		g_world.player.turnDirection = 1;
	else if (key_code == LEFT_ARROW)
		g_world.player.turnDirection = -1;
	else if (key_code == K_W)
		g_world.player.walkDirection = 1;
	else if (key_code == K_S)
		g_world.player.walkDirection = -1;		
	return (1);
}

int		key_released(int key_code, void *p)
{
	(void)p;
	if (key_code == RIGHT_ARROW)
		g_world.player.turnDirection = 0;
	else if (key_code == LEFT_ARROW)
		g_world.player.turnDirection = 0;
	else if (key_code == K_W)
		g_world.player.walkDirection = 0;
	else if (key_code == K_S)
		g_world.player.walkDirection = 0;
	return (1);
}

int 	mouse(int x, int y)
{
	if (!is_out_of_window(new_vector(x,y)))
	{
		//printf("x : %d | y : %d\n", x , y);
		if ((x >= SWIDTH - 30) && x < SWIDTH)
			TURNDIRECTION = 1;
		else if ((x <= 30) && x > 0)
			TURNDIRECTION = -1;
		else
			TURNDIRECTION = 0;
	}
	return 1;
}