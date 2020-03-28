/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:21:54 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/28 21:42:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include<time.h>

int *g_p;

void    init_world()
{
	g_world.player.walkDirection = 0;
	g_world.player.turnDirection = 0;
	g_world.player.rotation.speed = 5 * 0.0174533;
	g_world.player.speed = 20;
	g_world.player.offset = 0;
	g_world.player.coins = 0;
	g_world.player.maxhealth = 100;
	g_world.player.currenthealth = 60;
	g_world.gravity = 0;
}

t_image img;

void    setup()
{
	init_world();
	g_world.grid_size = new_shape( 64, 64);
	g_window = mlx_new_window(g_mlx, g_screen.width, g_screen.height, "cube3D");
	img.img = mlx_new_image(g_mlx, g_screen.width, g_screen.height);
	g_p = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);
	g_world.wall_rays = sf_malloc(sizeof(t_ray) * (g_screen.width + 1));
	show_sprites();
	update_field_of_view();
	mlx_put_image_to_window(g_mlx, g_window, img.img , 0, 0);
}

void	draw_health_bar()
{

	//g_world.sprites[g_world.numofsprites] = sprite;
}

void	update_sprite_frames()
{
	int	i;

	i = -1;
	while (++i < g_world.numofsprites)
	{
		if (g_world.sprites[i].anim.is_running)
		{
			g_world.sprites[i].anim.currentframe++;
		//	printf("%d\n", g_world.sprites[i].anim.currentframe);
			if (g_world.sprites[i].anim.currentframe == g_world.sprites[i].anim.nofframes)
			{
				if (g_world.sprites[i].anim.is_loop == 0)
					g_world.sprites[i].anim.is_running = 0;
				g_world.sprites[i].anim.currentframe = 0;
			}
		}
	}
}

int    update(int key)
{
	(void)key;
	int	i;

	//if (mlx_hook(g_window, 2, (1L << 0), key_pressed, (void*)0))
	//{
		update_field_of_view();
		update_sprites();
	//}
	//mlx_hook(g_window, 3, (1L << 0), key_released, (void*)0);
	update_player();
	show_sprites();
	draw_weapon();
	update_sprite_frames();
	t_vector a;
	a.x = PLAYERPOS.x - g_world.sprites[0].pos.x; 
	a.y = PLAYERPOS.y - g_world.sprites[0].pos.y;
	//if (!wall_at())
	g_world.sprites[0].pos.x += a.x / 100;
	g_world.sprites[0].pos.y += a.y / 100;
	if (g_world.player.height != 0 && g_world.player.height > 0)
			g_world.player.height -= g_world.gravity;
	mlx_put_image_to_window(g_mlx, g_window, img.img , 0, 0);
	background(0);
	return (0);
}

void	play_bc_music()
{
	pid = fork();
	if (pid == -1)
		handle_error(PROCCESS_CANT_BE_CREATED, FAIL);
	else if (pid == 0)
		system("mpg123 -q -loop 1000 assets/sounds/bc.mp3");
}

int   main(int ac, char **av)
{
	if (ac == 1)
	{
		perror("NOT VALID NUMBER OF ARGS");
		exit(FAIL);
	}
	g_world.numofsprites = 0;
	g_world.player.rotation.angle = 0;
	g_mlx = mlx_init();
	read_file(av[1]);
	//play_bc_music();
	setup();
	if (ac == 3 && ft_strcmp(av[2], "--save") == 0)
	{
		save_first_frame_in_bmp_file();
		free_all(UNCOMPLETED);
	}
	mlx_loop_hook(g_mlx, update, (void*)0);
	mlx_hook(g_window, 6,0, mouse, (void*)0);
	mlx_hook(g_window, 2, (1L << 0), key_pressed, (void*)0);
	mlx_hook(g_window, 3, (2L << 0), key_released, (void*)0);
	mlx_loop(g_mlx);
	return 0;
}
