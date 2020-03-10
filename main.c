/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:21:54 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/10 03:56:06 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include<time.h>

int *g_p;

int   draw_map()
{
	int i = -1, k = 0;
	int j;

	while(++i < g_world.rows)
	{
		j = 0;
		while (j < g_world.cols)
		{
			if (ft_strchr("NWSDE", g_game_map[i][j]))
			{
				t_vector a = new_vector(BLOCK_SIZE * j + BLOCK_SIZE / 2, BLOCK_SIZE * i + BLOCK_SIZE / 2);
				if (!g_is_keypressed)
					g_world.player.position = a;
				if (g_game_map[i][j] == 'N')
					g_world.player.rotation.angle = 90;
				else if (g_game_map[i][j] == 'S')
					g_world.player.rotation.angle = -90;
				else if (g_game_map[i][j] == 'W')
					  g_world.player.rotation.angle = 0;
				else
						g_world.player.rotation.angle = 180;
			}
			printf("%c ", g_game_map[i][j]);
			j++;
		}
		printf("\n");
	}
	return (1);
}

void  *pc(void *content)
{
	printf("[%s]\n", (char*)((t_pair*)content)->b);
	return NULL;
}

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
	char  *data;
	int texture_height;
	int texture_width;
	init_world();
	g_world.grid_size = new_shape( 64, 64);
	g_window = mlx_new_window(g_mlx, g_screen.width, g_screen.height, "cube3D");
	img.img = mlx_new_image(g_mlx, g_screen.width, g_screen.height);
	g_p = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);
	g_world.wall_rays = sf_malloc(sizeof(t_ray) * (g_screen.width + 1));
	mlx_string_put(g_mlx, g_window, SWIDTH /2 , SHEIGHT /2 , 0xff, "hello");
	show_sprites();
	draw_map();
	show_sprites();
	update_field_of_view();
	mlx_put_image_to_window(g_mlx, g_window, img.img , 0, 0);
	//mlx_put_image_to_window(g_mlx, g_window, img.img , 0, 0);		
}

void	draw_cursor()
{
	int i;

	i = -1;
	while (++i < 60)
		put_pixel(new_vector(SWIDTH / 2 - i, SHEIGHT / 2), RED);
	i = -1;
	while (++i < 60)
		put_pixel(new_vector(SWIDTH / 2 - 30, SHEIGHT / 2 - i + 30), RED);
}

void	draw_health_bar()
{

	//g_world.sprites[g_world.numofsprites] = sprite;
}

int    update(int key)
{
	(void)key;
	int j;
	float f;
	int i = 0;
	if (mlx_hook(g_window, 2, 0, key_pressed, (void*)0))
	{
		update_field_of_view();
		update_sprites();
	}
	mlx_hook(g_window, 3, 0, key_released, (void*)0);
	update_player();
	show_sprites();
	float ystep = g_world.sprites[0].img.height / (SHEIGHT / 3);
	float xStep = g_world.sprites[0].img.width / (SWIDTH / 3);
	float x = 0;
	while (++i < (SWIDTH / 3))
	{
		j = 0;
		f = 0;
		while (++j < (SHEIGHT / 3))
		{
			int pixel = g_world.sprites[0].img.data[(int)f * g_world.sprites[0].img.width + (int)x];
			if (pixel != 0)
				put_pixel(new_vector(i - g_world.sprites[0].img.width, j) , pixel);
			f += (float)ystep;
		}
		x += xStep;
	} 
	//draw_cursor();
	i = -1;
	while (++i < g_world.numofsprites)
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
	mlx_string_put(g_mlx, g_window, SWIDTH /2 , SHEIGHT /2 , 0xff, "hello");
	//i = -1;
//		while (++i < 1000 && )
	if (g_world.player.height != 0 && g_world.player.height > 0)
			g_world.player.height -= g_world.gravity;
	mlx_put_image_to_window(g_mlx, g_window, img.img , 0, 0);
	background(0);
	return (0);
}

void	init_game()
{
	
	pid = fork();
	if (pid == -1)
		handle_error(PROCCESS_CANT_BE_CREATED, FAIL);
	else if (pid == 0)
		system("mpg123 -q -loop 1000 assets/sounds/bc.mp3");
}
/*
void	snowFlack()
{
	t_snow snow;

	snow.x = 0;
	snow.y = random(-50, 0);
	snow.angle = random(0, 2 * PI);
	this.size = random(2, 5);

  // radius of snowflake spiral
  // chosen so the snowflakes are uniformly spread out in area
   this.radius = sqrt(random(pow(width / 2, 2)));
}
*/
//#include "valg/malloc.h"

int   main(int ac, char **av)
{
	if (ac == 1)
	{
		perror("NOT VALID NUMBER OF ARGS");
		exit(FAIL);
	}
	g_frame = 0;
	g_world.rows = 0;
	g_world.cols = 0;
	g_world.numofsprites = 0;
	g_mlx = mlx_init();
	read_file(av[1]);
	//init_game();
	/*printf("%d | %d\n", g_world.rows, g_world.cols);
	setup();
	if (ac == 3 && ft_strcmp(av[2], "--save") == 0)
	{
		save_first_frame_in_bmp_file();
		free_all(UNCOMPLETED);
	}
	mlx_loop_hook(g_mlx, update, (void*)0);
	mlx_hook(g_window, 6,0, mouse, (void*)0);
	mlx_loop(g_mlx);
	leakcheck();
	system("valgrind ./a.out");*/
	return 0;
}
