/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 03:18:48 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/03 08:25:59 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	render3D(t_ray ray, int col, t_vector Wall_hit, int is_hor_hit)
{
	float distanceFromRay = ray.distance * cos(ray.angle - g_world.player.rotation.angle);
	float distanceFromProjectionPlane = (g_screen.width / 2) / tan(VIEW_ANGLE / 2);
	float WALL_HEIGHT = (g_world.grid_size.width / distanceFromRay) * distanceFromProjectionPlane;
	double alpha = 1000 / distanceFromRay;
	float sky_height = (g_screen.height - (float)WALL_HEIGHT ) / 2;
	direct_line(col, 0, sky_height, g_world.colors[skybox]);
	direct_line(col, WALL_HEIGHT + sky_height, g_screen.height, g_world.colors[ground]);
	t_image texture;
	if (is_hor_hit)
	{
		if (sin(ray.angle) > 0)
			texture = g_textures[north_texture];	
		else
			texture = g_textures[south_texture];
	}else
	{
		if (cos(ray.angle) > 0)
			texture = g_textures[east_texture];
		else
			texture = g_textures[west_texture];
	}
    //direct_line(col, sky_height, sky_height + WALL_HEIGHT, shadow(0xffffff, distanceFromRay));
	render_texture(texture, WALL_HEIGHT, col, Wall_hit, is_hor_hit, distanceFromRay);
	//float sprite_distance = dist(g_world.sprites[0].pos, PLAYERPOS);
	//if (sprite_distance < ray.distance)
		//render_sprite(g_world.sprites[0], WALL_HEIGHT, col, Wall_hit, is_hor_hit, distanceFromRay);
}

void	render(t_ray ray, t_vector A)
{
	t_vector playerPosition;
	playerPosition = g_world.player.position;
	line(	playerPosition.x,  
			playerPosition.y,
			A.x,
			A.y,
			ray.color);
}


void	render_texture(t_image texture, int WALL_HEIGHT, int col, t_vector Wall_hit, int is_hor_hit, int distance)
{
	float	offset;
	float	step;
	float	yoffset;
	float	f;
	float	limit;
	float	y;

	limit = WALL_HEIGHT + (g_screen.height - WALL_HEIGHT ) / 2;
	y = (g_screen.height - (float)WALL_HEIGHT ) / 2;
	step = (float)texture.height / (float)WALL_HEIGHT;
	offset = is_hor_hit ? fmod(Wall_hit.x ,BLOCK_SIZE): fmod(Wall_hit.y, BLOCK_SIZE);
	f = 0;
	while (y < limit)
	{
		int pixel = texture.data[((int)(f) * texture.width + (int)offset)];
		put_pixel(new_vector(col, y) , pixel);
		f += step;
		y++;
	}
}

void	render_sprite(t_sprite sprite)
{
/*
	float	offset;
	float	step;
	float	yoffset;
	float	f;
	float	limit;
	float	y;

	limit = g_world.sprites[0].img.height;
	y = (g_screen.height - (float)WALL_HEIGHT ) / 2;
	offset = is_hor_hit ? fmod(Wall_hit.x ,BLOCK_SIZE): fmod(Wall_hit.y, BLOCK_SIZE);
	f = 0;
	while (y < limit)
	{
		//if ()
		int pixel = sprite.img.data[((int)(f) * sprite.img.width + (int)offset)];
		put_pixel(new_vector(col, y) , pixel);
		y++;
	}
*/
}