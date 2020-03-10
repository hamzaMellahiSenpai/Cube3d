/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 03:18:48 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/09 00:51:39 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	render3D(t_ray ray, int col, t_vector Wall_hit, int is_hor_hit)
{
	float distanceFromRay = ray.distance * cos(ray.angle - g_world.player.rotation.angle);
	float distanceFromProjectionPlane = (g_screen.width / 2) / tan(VIEW_ANGLE / 2);
	float WALL_HEIGHT = (BLOCK_SIZE / distanceFromRay) * distanceFromProjectionPlane;
	double alpha = 1000 / distanceFromRay;
	float sky_height = g_world.player.offset + (g_screen.height - (float)WALL_HEIGHT ) / 2;
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
	render_texture(texture, WALL_HEIGHT, col, Wall_hit, is_hor_hit, distanceFromRay);
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

	limit = WALL_HEIGHT + (g_screen.height - WALL_HEIGHT ) / 2 + g_world.player.offset ;
	y = (g_screen.height - (float)WALL_HEIGHT ) / 2 + g_world.player.offset ;
	step = (float)texture.height / (float)WALL_HEIGHT;
	offset = is_hor_hit ? fmod(Wall_hit.x ,BLOCK_SIZE): fmod(Wall_hit.y, BLOCK_SIZE);
	f = 0;
	while (y < limit)
	{
		int pixel = texture.data[((int)(f) * texture.width + (int)offset)];
		put_pixel(new_vector(col, y) , shadow(pixel, distance));
		f += step;
		y++;
	}
}
	/*float step = 64 / (SHEIGHT / 2);
	float xStep = 64 / SWIDTH;
	float x = 0;
	while (++i < SWIDTH)
	{
		j = -1;
		f = 0;
		while (++j < SHEIGHT / 2)
		{
			int pixel = texture.data[(int)f * 64 + (int)x];
			put_pixel(new_vector(i, j) , pixel);
			f += (float)step;
		}
		x += xStep;
		printf("%f\n", xStep);
	}
		g_world.sprites[0].s_x = 0;
	g_world.sprites[0].s_y =0;
	g_world.sprites[0].pos = PLAYERPOS;
	*/