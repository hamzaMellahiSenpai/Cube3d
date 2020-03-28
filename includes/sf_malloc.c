/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sf_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 22:16:31 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/25 03:08:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	*sf_malloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		(handle_error(Allocation_Failed, FAIL));
	new_lst(ptr);
	return (ptr);
}

void	free_all(int status)
{
	deletelist(&g_world.adresses);
	exit(status);
}
