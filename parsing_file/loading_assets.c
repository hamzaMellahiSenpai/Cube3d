/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 02:35:21 by marvin            #+#    #+#             */
/*   Updated: 2020/03/25 02:35:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_file.h"

void	load_image(int i, t_string path, int type)
{
	check_for_file(path);
	if (type == TEXTURE)
	{
		g_textures[i].img = mlx_xpm_file_to_image(g_mlx, path, &g_textures[i].width, &g_textures[i].height);
		g_textures[i].data = (int *)mlx_get_data_addr(g_textures[i].img, &g_textures[i].bits_per_pixel, &g_textures[i].bits_per_pixel, &g_textures[i].endian);
	}
	else if(type == SPRITE)
	{
		g_world.sprites[i].img.img = mlx_xpm_file_to_image(g_mlx, path, &g_world.sprites[i].img.width, &g_world.sprites[i].img.height);
	 	g_world.sprites[i].img.data = (int *)mlx_get_data_addr(g_world.sprites[i].img.img, &g_world.sprites[i].img.bits_per_pixel, &g_world.sprites[i].img.bits_per_pixel, &g_world.sprites[i].img.endian);
		g_world.sprites[i].visible = 1;
	}
}

void	load_texture(t_string line, int index)
{
	t_string path;
	t_string *tab;

	if (g_infos[index])
		return (handle_error(DUPLICATE_TEXTURE, FAIL));
	tab = ft_split(line, ' ');
	if (tablen((void**)tab) != 2 || ft_strlen(tab[0]) != 2)
		return (handle_error(INVALID_PATH, FAIL));
	path = ft_strjoin(tab[1], ".xpm", 3);
	load_image(index, path, TEXTURE);
	//printf("%s has been loaded\n", path);
}

void	load_sprite(t_string line, int index)
{
	t_string	*tab;
	t_sprite	sprite;
	t_string	*tab2;

	tab = ft_split(line, '|');
	tab2 = ft_split(tab[0], ' ');
	if (tablen((void**)tab2) != 2)
		return (handle_error(INVALID_SPRITE_ARG, FAIL));
	sprite.path = ft_strjoin(tab2[1], ".xpm", 3);
	sprite.type = tab2[0][1];
	validate_args(&tab, 9);
	sprite.anim.isPlayOnAwake = ft_atoi(tab[3]);
	sprite.anim.is_running = sprite.anim.isPlayOnAwake ? 1 : 0;
	sprite.anim.nofframes = ft_atoi(tab[4]);
	sprite.anim.is_loop = ft_atoi(tab[5]);
	sprite.anim.fps = ft_atoi(tab[6]);
	sprite.n = ft_atoi(tab[7]);
	sprite.bc = ft_atoi(tab[8]);
	sprite.pos_in_map = new_vector(ft_atoi(tab[1]), ft_atoi(tab[2]));
	sprite.pos.x = sprite.pos_in_map.x * BLOCK_SIZE + BLOCK_SIZE / 2;
	sprite.pos.y = sprite.pos_in_map.y * BLOCK_SIZE + BLOCK_SIZE / 2;
	sprite.anim.currentframe = 0;
	sprite.is_static = (sprite.type == 'G' || sprite.type == 'B') ? 1 : 0;
	sprite.y_offset = tab2[0][1] == 'G' ? 1 : 0;
	g_world.sprites[index - 4 + g_world.numofsprites] = sprite;
	load_image(index - 4 +  g_world.numofsprites, sprite.path, SPRITE);
	//print_vector(sprite.pos_in_map);
	//fillCell(sprite.pos_in_map.x,sprite.pos_in_map.y,sprite.type);
	g_world.numofsprites++;
}
