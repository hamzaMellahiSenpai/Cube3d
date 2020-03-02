/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:21:54 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/02 06:47:59 by hmellahi         ###   ########.fr       */
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
      if (g_game_map[i][j] == '4')
        g_world.object_position = new_vector(g_world.grid_size.width * j, g_world.grid_size.height * i); 
      else if (g_game_map[i][j] == '3')
      {
        t_vector a = new_vector(g_world.grid_size.width * j + g_world.grid_size.width / 2, g_world.grid_size.height * i + g_world.grid_size.height / 2);
          if (!g_is_keypressed)
            g_world.player.position = a; 
            //g_world.player.position = mult_vectors(&a, &MINI_MAP_SCALE, VEC_TO_NUM);
           // g_world.player.position = new_vector(164.641571, 53.678028);
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

  printf("Hello!\n");
  lstiter(g_world.images, pc);
  //lstiter(g_world.images, f);
}

void    init_world()
{
  g_world.player.walkDirection = 0;
  g_world.player.turnDirection = 0;
  g_world.player.rotation.angle = 0;
  g_world.player.rotation.speed = 5 * 0.0174533;
  g_world.player.speed = 6;
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
  printf("creating an image\n");
  img.img = mlx_new_image(g_mlx, g_screen.width, g_screen.height);
  g_p = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);
  img.bits_per_pixel = 3;
  // g_textures[north_texture].img = mlx_xpm_file_to_image(g_mlx, "greystone.xpm", &g_textures[north_texture].width, &g_textures[north_texture].height);
  // g_textures[north_texture].data = (int *)mlx_get_data_addr(g_textures[north_texture].img, &g_textures[north_texture].bits_per_pixel, &g_textures[north_texture].bits_per_pixel, &g_textures[north_texture].endian);
  // g_textures[south_texture].img = mlx_xpm_file_to_image(g_mlx, "redbrick.xpm", &g_textures[south_texture].width, &g_textures[south_texture].height);
  // g_textures[south_texture].data = (int *)mlx_get_data_addr(g_textures[south_texture].img, &g_textures[south_texture].bits_per_pixel, &g_textures[south_texture].bits_per_pixel, &g_textures[south_texture].endian);
  // g_textures[east_texture].img = mlx_xpm_file_to_image(g_mlx, "colorstone.xpm", &g_textures[east_texture].width, &g_textures[east_texture].height);
  // g_textures[east_texture].data = (int *)mlx_get_data_addr(g_textures[east_texture].img, &g_textures[east_texture].bits_per_pixel, &g_textures[east_texture].bits_per_pixel, &g_textures[east_texture].endian);
  // g_textures[west_texture].img = mlx_xpm_file_to_image(g_mlx, "bluestone.xpm", &g_textures[west_texture].width, &g_textures[west_texture].height);
  // g_textures[west_texture].data = (int *)mlx_get_data_addr(g_textures[west_texture].img, &g_textures[west_texture].bits_per_pixel, &g_textures[west_texture].bits_per_pixel, &g_textures[west_texture].endian);
  load_assets();
  update_field_of_view();
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
  if (mlx_hook(g_window, 2, 0, key_pressed, (void*)0))
    update_field_of_view();
  mlx_hook(g_window, 3, 0, key_released, (void*)0);
  update_player();
  mlx_hook(g_window, 4, 0, mouse_press_hook, (void*)0);
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
