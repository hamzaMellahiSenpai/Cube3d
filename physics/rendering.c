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

void	pick_texture(t_image *texture, int is_hor_hit, t_ray ray)
{
	if (is_hor_hit)
	{
		if (sin(ray.angle) > 0)
			*texture = g_textures[north_texture];
		else
			*texture = g_textures[south_texture];
	}
	else
	{
		if (cos(ray.angle) > 0)
			*texture = g_textures[east_texture];
		else
			*texture = g_textures[west_texture];
	}
}

void	render_walls(t_ray ray, int col, t_vector Wall_hit, int is_hor_hit)
{
	float		distancefromray;
	float		distfromprojectionplane;
	float		wall_height;
	float		sky_height;
	t_image		texture;

	distancefromray = ray.distance * cos(ray.angle - g_world.player.rotation.angle);
	distfromprojectionplane = (g_screen.width / 2) / tan(VIEW_ANGLE / 2);
	wall_height = (BLOCK_SIZE / distancefromray) * distfromprojectionplane;
	sky_height = g_world.player.offset + (g_screen.height - (float)wall_height) / 2;
	direct_line(col, 0, sky_height, g_world.colors[skybox]);
	direct_line(col, wall_height + sky_height, g_screen.height, g_world.colors[ground]);
	pick_texture(&texture, is_hor_hit, ray);
	render_texture(texture, wall_height, col, Wall_hit, is_hor_hit, distancefromray);
}

void	render_texture(t_image texture, int wall_height, int col, t_vector Wall_hit, int is_hor_hit, int distance)
{
	float	offset;
	float	step;
	float	f;
	float	limit;
	float	y;
	int		pixel;

	limit = wall_height + (g_screen.height - wall_height) / 2 + g_world.player.offset;
	y = (g_screen.height - (float)wall_height ) / 2 + g_world.player.offset;
	step = (float)texture.height / (float)wall_height;
	offset = is_hor_hit ? fmod(Wall_hit.x, BLOCK_SIZE) : fmod(Wall_hit.y, BLOCK_SIZE);
	f = 0;
	while (y < limit)
	{
		pixel = texture.data[((int)(f) * texture.width + (int)offset)];
		put_pixel(new_vector(col, y), shadow(pixel, distance));
		f += step;
		y++;
	}
}
