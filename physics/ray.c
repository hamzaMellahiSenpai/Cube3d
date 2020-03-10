/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:33:22 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/06 22:32:50 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_ray	new_ray(float rayAngle)
{
	t_ray ray;

	ray.angle = norm_angle(rayAngle);
	ray.distance = 0;
	ray.isFacingRight = ((ray.angle < (M_PI / 2)) || (ray.angle > (1.5 * M_PI)));
	ray.isFacingLeft = !ray.isFacingRight;
	ray.isFacingDown = (ray.angle >= 0 && ray.angle <= M_PI);
	ray.isFacingUp = !ray.isFacingDown;
	ray.color = 0xFF0000;
	return (ray);
}

t_vector	get_horizontal_intersection(t_ray ray, int *hor_found)
{
	t_vector A;
	t_vector step;
	t_vector P;

	P = g_world.player.position;
	A.y = floor(P.y / BLOCK_SIZE) * BLOCK_SIZE;
	A.y += ray.isFacingDown ? BLOCK_SIZE : -0.0001;
	
	A.x = (A.y - P.y) / tan(ray.angle) + P.x;
	
	step.y = BLOCK_SIZE;
	step.y *= ray.isFacingUp ? -1 : 1;
	
	step.x = BLOCK_SIZE / tan(ray.angle);
	step.x *= (ray.isFacingLeft && step.x > 0) ? -1 : 1;
	step.x *= (ray.isFacingRight && step.x < 0) ? -1 : 1;
	while (!is_out_of_window(A))
	{
		if (wall_at(A))
		{
			*hor_found = 1;
			break;
		}
		add_to_vector(&A, &step, VEC_TO_VEC);
	}
	return (A);
}

t_vector	get_vertical_intersection(t_ray ray, int *ver_found)
{
	t_vector B;
	t_vector step;
	t_vector P;

	P = g_world.player.position;
	B.x = floor(P.x / BLOCK_SIZE) * BLOCK_SIZE;
	B.x += ray.isFacingRight ? BLOCK_SIZE : -0.001;
	B.y = P.y + tan(ray.angle) * (B.x - P.x);
	step.x = BLOCK_SIZE;
	step.x *= ray.isFacingLeft ? -1 : 1;
	step.y = BLOCK_SIZE * tan(ray.angle);
	step.y *= (ray.isFacingUp && step.y > 0) ? -1 : 1;
	step.y *= (ray.isFacingDown && step.y < 0) ? -1 : 1;
	while (!is_out_of_window(B))
	{
		if (wall_at(B))
		{
			*ver_found = 1;
			break;
		}
		add_to_vector(&B, &step, VEC_TO_VEC);
	}
	return (B);
}

void	cast(t_ray *a, int col)
{
	t_vector A;
	t_vector B;
	int	hor_found;
	int ver_found;
	int	is_hor_hit = 1;
	t_ray ray = *a;

	ray.isFacingRight = ((ray.angle < (M_PI / 2)) || (ray.angle > (1.5 * M_PI)));
	ray.isFacingLeft = !ray.isFacingRight;
	ray.isFacingDown = (ray.angle >= 0 && ray.angle <= M_PI);
	ray.isFacingUp = !ray.isFacingDown;
	hor_found = 0;
	ver_found = 0;
	A = get_horizontal_intersection(ray, &hor_found);
	B = get_vertical_intersection(ray, &ver_found);
	float hor_hit_distance = hor_found ? dist(A, g_world.player.position) : 90000000;
	float ver_hit_distance = ver_found ? dist(B, g_world.player.position) : 90000000;
	if (hor_hit_distance > ver_hit_distance)
	{
		is_hor_hit = 0;
		A = B;
	}
	ray.distance = dist(A, g_world.player.position);
	*a = ray;
	render_walls(ray, col, A, is_hor_hit);
}
