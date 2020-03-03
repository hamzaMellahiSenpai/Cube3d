/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 02:12:08 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/03 04:38:12 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int		shadow(int color, double distance)
{
	int r;
	int g;
	int b;
	float fact;

	fact = 128 / distance;
	b = (color & 0xff) * fact;
	b = b > (color & 0x000000ff) ? (color & 0x000000ff) : b;
	color = color >> 8;
	g = (color & 0x000000ff) * fact;
	g = g > (color & 0x000000ff) ? (color & 0x000000ff) : g;
	color = color >> 8;
	r = (color & 0x0000ff) * fact;
	r = r > (color & 0x000000ff) ? (color & 0x000000ff) : r;
	return (rgb_to_int(r,g,b));
}
