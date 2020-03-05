/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:21:54 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/05 03:44:34 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include<time.h>

int *g_p;

int   draw_map()
{
	int i = -1;
	int j;

	while(++i < g_world.rows)
	{
		j = 0;
		while (j < g_world.cols)
		{
			//if (g_game_map[i][j] == '0')
				//cube(new_vector(g_world.grid_size.width * j,i * g_world.grid_size.height), g_world.grid_size.width, 0x000000);
		 /*if (g_game_map[i][j] == '1')
				draw_square(i, j, g_world.grid_size);*/
			if (g_game_map[i][j] == '3')
				g_world.sprites[0].pos = new_vector(g_world.grid_size.width * j + g_world.grid_size.width / 2 , g_world.grid_size.height * i + g_world.grid_size.width / 2); 
				//g_world.sprites[0].pos = new_vector(g_screen.width / g_world.cols * j, g_screen.height / g_world.rows * i);
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
	//g_world.grid_size.width = g_screen.width / g_world.rows;
	//g_world.grid_size.height = g_screen.height / g_world.cols;
	g_window = mlx_new_window(g_mlx, g_screen.width, g_screen.height, "cube3D");
	img.img = mlx_new_image(g_mlx, g_screen.width, g_screen.height);
	g_p = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);
	g_world.wall_rays = malloc(sizeof(t_ray) * (g_screen.width + 1));
	check_for_file("assets/textures/greystone.xpm");
	g_textures[north_texture].img = mlx_xpm_file_to_image(g_mlx, "assets/textures/greystone.xpm", &g_textures[north_texture].width, &g_textures[north_texture].height);
	g_textures[north_texture].data = (int *)mlx_get_data_addr(g_textures[north_texture].img, &g_textures[north_texture].bits_per_pixel, &g_textures[north_texture].bits_per_pixel, &g_textures[north_texture].endian);
	check_for_file("assets/textures/redbrick.xpm");
	g_textures[south_texture].img = mlx_xpm_file_to_image(g_mlx, "assets/textures/redbrick.xpm", &g_textures[south_texture].width, &g_textures[south_texture].height);
	g_textures[south_texture].data = (int *)mlx_get_data_addr(g_textures[south_texture].img, &g_textures[south_texture].bits_per_pixel, &g_textures[south_texture].bits_per_pixel, &g_textures[south_texture].endian);
	check_for_file("assets/textures/colorstone.xpm");
	g_textures[east_texture].img = mlx_xpm_file_to_image(g_mlx, "assets/textures/colorstone.xpm", &g_textures[east_texture].width, &g_textures[east_texture].height);
	g_textures[east_texture].data = (int *)mlx_get_data_addr(g_textures[east_texture].img, &g_textures[east_texture].bits_per_pixel, &g_textures[east_texture].bits_per_pixel, &g_textures[east_texture].endian);
	check_for_file("assets/textures/bluestone.xpm");
	g_textures[west_texture].img = mlx_xpm_file_to_image(g_mlx, "assets/textures/bluestone.xpm", &g_textures[west_texture].width, &g_textures[west_texture].height);
	g_textures[west_texture].data = (int *)mlx_get_data_addr(g_textures[west_texture].img, &g_textures[west_texture].bits_per_pixel, &g_textures[west_texture].bits_per_pixel, &g_textures[west_texture].endian);
	check_for_file("assets/sprites/barrel.xpm");
	g_world.sprites[0].img.img = mlx_xpm_file_to_image(g_mlx, "assets/sprites/barrel.xpm", &g_world.sprites[0].img.width, &g_world.sprites[0].img.height);
	g_world.sprites[0].img.data = (int *)mlx_get_data_addr(g_world.sprites[0].img.img, &g_world.sprites[0].img.bits_per_pixel, &g_world.sprites[0].img.bits_per_pixel, &g_world.sprites[0].img.endian);
	//load_assets();
	mlx_put_image_to_window(g_mlx, g_window, img.img , 0, 0);
	printf("%d | %d\n", g_world.rows, g_world.cols);
	draw_map();
}

int   mouse_press_hook(int key, void *img)
{
	printf("yesss");
	return (1);
}

int    update(int key)
{
	(void)key;
	int i  = -1,j;
	int f = 0;
	t_image texture = g_textures[0];
	int step = texture.height / (SHEIGHT / 2);
	update_sprites();
	while (++i < SWIDTH)
	{
		j = -1;
		f = 0;
		while (++j < SHEIGHT / 2)
		{
				int pixel = texture.data[((int)(f) * texture.width + i)];
				put_pixel(new_vector(i, j) , pixel);
				f += step;
		}
	}
	if (mlx_hook(g_window, 2, 0, key_pressed, (void*)0))
		update_field_of_view();
	mlx_hook(g_window, 3, 0, key_released, (void*)0);
	update_player();
	mlx_hook(g_window, 4, 0, mouse_press_hook, (void*)0);
	show_sprites();
	mlx_put_image_to_window(g_mlx, g_window, img.img , 0, 0);
	background(0x00);
	return (0);
}

int   main(int ac, char **av)
{
	if (ac != 2)
	{
		perror("NOT VALID NUMBER OF ARGS");
		exit(FAIL);
	}
	g_world.rows = 0;
	g_world.cols = 0;
	g_mlx = mlx_init();
	read_file(av[1]);
	setup();
	mlx_loop_hook(g_mlx, update, (void*)0);
	mlx_loop(g_mlx);
}
