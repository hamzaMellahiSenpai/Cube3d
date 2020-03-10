/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:33:48 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/05 01:21:28 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_vector		new_vector(float x, float y)
{
	t_vector vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_shape			new_shape(float width, float height)
{
	t_shape shape;

	shape.width = width;
	shape.height = height;
	return (shape);
}

void			print_vector(t_vector a)
{
	printf("\n x : %f, y : %f \n", a.x, a.y);
}

float			dist(t_vector a, t_vector b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

t_vector		add_vectors(t_vector *a, t_vector *b)
{
	return (new_vector(a->x + b->x, a->y + b->y));
}

void			add_to_vector(void *a, void *b, char type)
{
	if (type == VEC_TO_VEC)
	{
		((t_vector*)a)->x += ((t_vector*)b)->x;
		((t_vector*)a)->y += ((t_vector*)b)->y;
	}
	else if (type == VEC_TO_NUM)
	{
		((t_vector*)a)->x += *((int*)b);
		((t_vector*)a)->y += *((int*)b);
	}
	else
	{
		perror("Please Enter Valid arguments!!!----");
		exit(0);
	}
}
