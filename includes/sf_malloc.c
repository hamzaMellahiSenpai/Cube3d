/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sf_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 22:16:31 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/06 21:42:51 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	*sf_malloc(size_t size)
{
	void	*ptr;
	t_lst	*lst;

	if (!(ptr = malloc(size)))
		(handle_error(Allocation_Failed, FAIL));
	lst = new_lst(ptr);
	return (ptr);
}

void	free_all(int status)
{
	deletelist(&g_world.adresses);
	exit(status);
}
