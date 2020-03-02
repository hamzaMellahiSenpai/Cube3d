/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:33:48 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/01 00:27:28 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_vector  new_vector(float x, float y)
{
	t_vector vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_shape   new_shape(float _width, float _height)
{
	t_shape shape;

	shape.width = _width;
	shape.height = _height;
	return (shape);
}

t_shape   to_shape(t_vector a)
{
	t_shape shape;

	shape.width = a.x;
	shape.height = a.y;
	return (shape);
}

void			print_vector(t_vector a)
{
	//printf("\n x : %f, y : %f \n", a.x, a.y);
}

float			vector_len(t_vector vec)
{
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

float			dist(t_vector a, t_vector b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

t_vector	add_vectors(void *a, void *b)
{
	t_vector	c;

	/*if (get_type(a) == "Vector" && get_type(b) == "Vector")
		c = *new_vector(a.x + b.x, a.y + b.y);
	else if (get_type(a) == "Vector" && get_type(b) == "Number")
		c = *new_vector(a.x + b, a->y + b);
	else if (get_type(b) == "Vector" && get_type(a) == "Number")
		c = *new_vector(a + b->x, a + b->y);
	else
		perror("Please Enter Valid arguments!!!----");*/
	c = new_vector(((t_vector*)a)->x + ((t_vector*)b)->x, ((t_vector*)a)->y + ((t_vector*)b)->y);
	return (c);
}

t_vector 	substract_vectors(void *_a, void *_b, int type)
{
	t_vector c;

	if (type == 0)
		c = new_vector(((t_vector*)_a)->x - ((t_vector*)_b)->x,
			((t_vector*)_a)->y - ((t_vector*)_b)->y);
	else if (type == 1)
		c = new_vector(((t_vector*)_a)->x - *((int*)_b), 
			((t_vector*)_a)->y - *((int*)_b));
	else if (type == 2)
		c = new_vector(*((int*)_a) - ((t_vector*)_b)->x, 
			*((int*)_a) - ((t_vector*)_b)->y);
	else
	{
		perror("Please Enter Valid arguments!!!----");
		exit(0);
	}
	return (c);
}

t_vector	mult_vectors(void *a, void *b, int type)
{
	t_vector	c;

	if (type == VEC_TO_VEC)
		c = new_vector(((t_vector*)a)->x * ((t_vector*)b)->x, ((t_vector*)a)->y * ((t_vector*)b)->y);
	else if (type == VEC_TO_NUM)
		c = new_vector(((t_vector*)a)->x * *((float*)b), ((t_vector*)a)->y * *((float*)b));
	else if (type == NUM_TO_VEC)
		c = new_vector(*((int*)a) * ((t_vector*)b)->x, *((int*)a) * ((t_vector*)b)->y);
	else
	{
		perror("Please Enter Valid arguments!!!----");
		exit(0);
	}
	return (c);
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