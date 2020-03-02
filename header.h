/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 01:08:43 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/02 05:42:43 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include "mlx.h"
# include <stdio.h>
# include <time.h>
# include <unistd.h>

# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define UP_ARROW 126
# define DOWN_ARROW 125
# define VIEW_ANGLE (float)1.0472
# define WALL 1
# define PP g_world.player.position
# define WALKDIRECTION g_world.player.walkDirection
# define TURNDIRECTION g_world.player.turnDirection
# define PROTATIONSPEED g_world.player.rotation.speed
# define MIN(a,b) (((a)<(b))?(a):(b))
# define MAX(a,b) (((a)>(b))?(a):(b))
# define BLOCK_SIZE 64
# define MINI_MAP_SCALE 1

enum							e_states
{
	UNCOMPLETED,
	FAIL
};

enum							e_file_infos
{
	north_texture,
	south_texture,
	east_texture,
	west_texture,
	sprite_texture,
	resolution,
	floor_color,
	ceil_color,
	player_position
};

enum							e_errors
{
	INVALID_FILE_NAME,
	MISSING_INFO,
	DUPLICATE_TEXTURE,
	DUPLICATE_COLOR,
	DUPLICATE_RESOLUTION,
	DRAWING_OUTSIDE_IMAGE,
	INVALID_MAP,
	NON_EXISTENECE_FILE
};

enum							e_space
{
	skybox,
	ground
};

enum							e_vectors_states
{
	VEC_TO_VEC,
	VEC_TO_NUM,
	NUM_TO_VEC
};

typedef	struct		s_vector
{
	float		x;
	float		y;
}									t_vector;

typedef	struct		s_pair
{
	void	*a;
	void	*b;
}									t_pair;

typedef	struct    s_shape
{
	float		width;
	float		height;
}									t_shape;

typedef struct		s_lst
{
	void	*content;
	struct s_lst	*next;
}					t_lst;

typedef	struct		s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
	int color;
}									t_color;

typedef	struct		s_rotation
{
	float angle;
	float speed;
}									t_rotation;

typedef struct		s_player
{
	t_vector			position;
	t_rotation		rotation;
	float					speed;
	t_vector			view;
	float					health;
	int						walkDirection;
	int						turnDirection;
}									t_player;

typedef struct		s_ray
{
	float		angle;
	double	distance;
	int			isFacingDown;
	int			isFacingRight;
	int			color;
	int			isFacingLeft;
	int			isFacingUp;
	int			type;
}									t_ray;

typedef struct		s_image
{
	void	*img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
	int		*data;
}									t_image;

typedef struct		s_sprite
{
	t_image		img;
	float			distance;
	t_vector	position;
}									t_sprite;

typedef struct		s_world
{
	t_shape				grid_size;
	int						rows;
	int						cols;
	t_player			player;
	int						sky_box_color;
	int						ground_color;
	t_vector			object_position;
	t_sprite			*sprites;
	t_lst						*images;
	int					colors[2];
}									t_world;

typedef	struct		s_texture
{
	int		*data;
	int		width;
	int		height;
}									t_texture;

typedef	struct		s_time
{
	float		old_time;
	float		current_time;
	float		delta_time;
}									t_time;

typedef char*			t_string;

void							*g_mlx;
void							*g_window;

t_world						g_world;
int								g_is_keypressed;
t_shape						g_screen;
char							g_game_map[100][100];
int								g_infos[9];
t_image						g_textures[20];
int							g_bc[2];
/*
================= Vectors Functions ===================
*/

t_vector		new_vector(float x, float y);
t_shape			new_shape(float x, float y);
t_vector		add_vectors(void *a, void *b);
void			print_vector(t_vector vector);
t_vector		substract_vectors(void *a, void *b, int type);
void			update_field_of_view();
float			vector_len(t_vector vec);
void			add_to_vector(void *a, void *b, char type);
t_vector		mult_vectors(void *a, void *b, int type);
t_shape			to_shape(t_vector a);
/*
=======================================================
*/

int				handle_input(int key, void *p);
void			update_player();
void			line(int x0, int y0, int x1, int y1, int color);
void			text(char *str, int x, int y);
float			deg_to_rad(int angle);
void			put_pixel(t_vector a, int color);
void			rect(t_vector position, float width, float height, int color);
void			draw_square(int row, int col, t_shape grid_size);
int				move_player(int key, void *p);
void			background(int color);
void			get_delta_time();
float			norm_angle(float angle);
int				walls_at(t_vector coordinate);
void			render(t_ray ray, t_vector a);
void			cast(t_ray *ray, int col);
t_ray			new_ray(float ray_angle);
void			render3D(t_ray ray, int col, t_vector wall_hit, int is_hor_hit);
float			modulo(float num, float divisor);
void			circle(t_vector a, int radius, int color);
/*================= Get Next Line function  ====================*/
int				get_next_line(int fd, char **line);

/*================= Utils Functions  ====================*/
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *str);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2, int index);
char			*ft_strcpy(char *dest, const char *src);
void			free_space(char **ptr);
int				ft_atoi(const char *str);
void			*ft_memset(void *p, int val, size_t size);
char			**ft_split(char const *s, char c);
int				numofdigits(int n);
int				ft_strcmp(const char *s1, const char *s2);
void			handle_error(int error_index, int status);
void			read_file(t_string file_name);
void			cube(t_vector a, int width, int color);
float			dist(t_vector a, t_vector b);
int				rgb_to_int(int r, int g, int b);
t_string		ft_strlcat(char *dst, const char *src);
void			line2(float x0, float y0, float x1, float y1, int color);
int				update();
/*=======================================================*/
int				key_pressed(int key_code, void *p);
int				key_released(int key_code, void *p);
/*========================================================*/
/*=========================================================*/
void			push_back(t_lst **alst, t_lst *new);
t_lst			*new_lst(void *content);
void			delete_lst(t_lst** head_ref);
t_pair			*make_pair(void *a, void *b);
void	lstiter(t_lst *lst, void *(*f)(void *content));
void			push_front(t_lst** head_ref, t_lst* new);
t_image   load_image(t_pair *content);
/*=========================================================*/
#endif
