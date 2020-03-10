/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 02:12:08 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/10 00:05:43 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		shadow(int color, double distance)
{
	int		r;
	int		g;
	int		b;
	float	fact;

	fact = 100 / distance;
	b = (color & 0xff) * fact;
	b = b > (color & 0xff) ? (color & 0xff) : b;
	color = color >> 8;
	g = (color & 0xff) * fact;
	g = g > (color & 0xff) ? (color & 0xff) : g;
	color = color >> 8;
	r = (color & 0xff) * fact;
	r = r > (color & 0xff) ? (color & 0xff) : r;
	return (rgb_to_int(r, g, b));
}
