/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:21:54 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/07 23:00:27 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include<time.h>

int *g_p;

int   draw_map()
{
	int i = -1;
	int j;
	int k;

	k = -1;
	while(++i < g_world.rows)
	{
		j = 0;
		while (j < g_world.cols)
		{
			//if (g_game_map[i][j] == '0')
				//cube(new_vector(g_world.grid_size.width * j,i * g_world.grid_size.height), g_world.grid_size.width, 0x000000);
		 /*if (g_game_map[i][j] == '1')
				draw_square(i, j, g_world.grid_size);*/
			if (g_game_map[i][j] == 'C')
			{
				if (++k < g_world.numofsprites)
				{
					g_world.sprites[k].pos_in_map = new_vector(j,i);
					g_world.sprites[k].pos = new_vector(g_world.grid_size.width * j + g_world.grid_size.width / 2 , g_world.grid_size.height * i + g_world.grid_size.width / 2); 
				}
				else
					handle_error(INVALID_MAP, FAIL);
			}
			else if (ft_strchr("NWSDE", g_game_map[i][j]))
			{
				t_vector a = new_vector(g_world.grid_size.width * j + g_world.grid_size.width / 2, g_world.grid_size.height * i + g_world.grid_size.height / 2);
				//t_vector a = new_vector(g_screen.width / g_world.cols * j, g_screen.height / g_world.rows * i);
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
			j++;
		}
	}
	return (1);
}

void  *pc(void *content)
{
	printf("[%s]\n", (char*)((t_pair*)content)->b);
	return NULL;
}

void    load_assets()
{
		void *(f);
		f = load_image;
		//f = pc;

	//printf("Hello!\n");
	//lstiter(g_world.images, pc);
	//lstiter(g_world.images, f);
}

void    init_world()
{
	g_world.player.walkDirection = 0;
	g_world.player.turnDirection = 0;
	g_world.player.rotation.speed = 5 * 0.0174533;
	g_world.player.speed = 20;
	g_world.player.offset = 0;
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
	mlx_put_image_to_window(g_mlx, g_window, img.img , 0, 0);
	printf("%d | %d\n", g_world.rows, g_world.cols);
	draw_map();
}

int 	mouse(int x, int y)
{
	if (!is_out_of_window(new_vector(x,y)))
	{
		printf("x : %d | y : %d\n", x , y);
		if ((x >= SWIDTH - 30) && x < SWIDTH)
			TURNDIRECTION = 1;
		else if ((x <= 30) && x > 0)
			TURNDIRECTION = -1;
		else
			TURNDIRECTION = 0;
	}
	return 1;
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
int    update(int key)
{
	(void)key;
	int j;
	float f;
	int i = 0;
	if (mlx_hook(g_window, 2, 0, key_pressed, (void*)0))
		update_field_of_view();
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
				put_pixel(new_vector(i + SWIDTH/3 - g_world.sprites[0].img.width, j + SHEIGHT *2/3) , pixel);
			f += (float)ystep;
		}
		x += xStep;
	}
	draw_cursor();
	mlx_put_image_to_window(g_mlx, g_window, img.img , 0, 0);
	background(0);
	g_frame++;
	g_frame %= 10000;
	return (0);
}
# include "val/malloc.h"

void	init_game()
{
	
	pid = fork();
	if (pid == -1)
		handle_error(PROCCESS_CANT_BE_CREATED, FAIL);
	else if (pid == 0)
		system("mpg123 -q -loop 1000 assets/sounds/bc.mp3");
}

int   main(int ac, char **av)
{
	if (ac != 2)
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
	//system(“COLOR 1A”);
	//init_game();
	setup();
	mlx_loop_hook(g_mlx, update, (void*)0);
	mlx_hook(g_window, 6,0, mouse, (void*)0);
	mlx_loop(g_mlx);
	//system("kill 0");
	//leakcheck();
	return 0;
}
