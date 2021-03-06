/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 09:51:10 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/10 23:54:20 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_string messages[16];

void		init_errors()
{
	messages[0] = "Invalid file name!";
	messages[1] = "Missing info";
	messages[2] = "Duplicate Texture";
	messages[3] = "Duplicate Color";
	messages[4] = "Duplicate Resolution";
	messages[5] = "Stop Idiot! You have reached the range of g_screen";
	messages[6] = "Invalid Map";
	messages[7] = "NO SUCH FILE OR DIRECTORY";
	messages[8] = "Allocation Failed";
	messages[9] = "PROCCESS_CANT_BE_CREATED";
	messages[10] = "INVALID_PATH";
	messages[11] = "INVALID_SPRITE_PLACEMENT";
	messages[12] = "INVALID_RESOLUTION";
	messages[13] = "DUPLICATION_PLAYER";
	messages[14] = "INVALID SPRITE ARGUMENT";
	messages[15] = "INVALID COLORS";
}

void		handle_error(int error_index, int status)
{
	perror(messages[error_index]);
	free_all(status);
}

void		check_for_file(t_string file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror(file_name);
		free_all(FAIL);
	}
}
