/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 01:08:43 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/10 23:38:44 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <math.h>
# include <stdlib.h>
//include "./valg/malloc.h"
# include <string.h>
# include "mlx.h"
# include <stdio.h>
# include <time.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define UP_ARROW 126
# define DOWN_ARROW 125
# define CTRL_KEY 256
# define EXIT_KEY 53
# define SPACE_KEY 49
# define W_KEY 13
# define A_KEY 0
# define D_KEY 2
# define S_KEY 1
# define SWIDTH g_screen.width
# define SHEIGHT g_screen.height
# define VIEW_ANGLE (float)1.0472
# define WALL 1
# define RED 0XFF0000
# define PP g_world.player.position
# define WALKDIRECTION g_world.player.walkDirection
# define TURNDIRECTION g_world.player.turnDirection
# define PROTATIONSPEED g_world.player.rotation.speed
# define PROTATIONANGLE g_world.player.rotation.angle
# define PLAYERPOS g_world.player.position
# define PLAYERH g_world.player.height
# define MIN(a,b) (((a)<(b))?(a):(b))
# define MAX(a,b) (((a)>(b))?(a):(b))
# define BLOCK_SIZE 64
# define MINI_MAP_SCALE 1
# define DEG(x) x * 180 / M_PI

int g_frame;

enum							e_states
{
	UNCOMPLETED,
	FAIL
};

enum							e_images
{
	SPRITE,
	TEXTURE
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
	NON_EXISTENECE_FILE,
	Allocation_Failed,
	PROCCESS_CANT_BE_CREATED,
	INVALID_PATH,
	INVALID_SPRITE_PLACEMENT,
	INVALID_RESOLUTION,
	DUPLICATE_PLAYER
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

typedef char*			t_string;

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
	int		width;
	int		height;
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
	float					offset;
	int					currenthealth;
	int					maxhealth;
	int					coins;
	int					height;
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

typedef	struct		s_animation
{
	int		isPlayOnAwake;
	int		is_loop;
	int		is_running;
	int		nofframes;
	int		currentframe;
	int		fps;
	int		isPlaying;
}					t_animation;

typedef struct		s_sprite
{
	t_image		img;
	float		distance;
	t_vector	pos;
	t_string	path;
	float		size;
	int			s_x;
	int			s_y;
	int			visible;
	t_vector	pos_in_map;
	t_animation	anim;
	int			is_static;
	int			bc;
	int			n;
	int			y_offset;
	int			type;
}									t_sprite;

typedef struct		s_world
{
	t_shape				grid_size;
	int						rows;
	int						cols;
	t_player			player;
	int						sky_box_color;
	int						ground_color;
	t_sprite			sprites[100];
	//t_lst						*sprites;
	int					colors[2];
	t_ray				*wall_rays;
	t_lst				*adresses;
	int					numofsprites;
	int					gravity;
	char				**map;
}									t_world;
pid_t pid;
pid_t tpid;

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
void	check_for_file(t_string file_name);
t_vector		new_vector(float x, float y);
t_shape			new_shape(float x, float y);
void			add_to_vector(void *a, void *b, char type);
t_vector		add_vectors(t_vector *a, t_vector *b);
void			print_vector(t_vector vector);
void			update_field_of_view();
void			direct_line(int x, int start, int end, int color);
void			render_texture(t_image texture, int WALL_HEIGHT, int col, t_vector Wall_hit, int is_hor_hit, int distance);
void			render_sprite(t_sprite sprite);
float			dist(t_vector a, t_vector b);
void			save_first_frame_in_bmp_file();
int		tablen(void **tab);
/*
=======================================================
*/

int				handle_input(int key, void *p);
void			update_player();
void			line(int x0, int y0, int x1, int y1, int color);
float			deg_to_rad(int angle);
void			put_pixel(t_vector a, int color);
void			rect(t_vector position, float width, float height, int color);
void			draw_square(int row, int col, t_shape grid_size);
int				move_player(int key, void *p);
void			background(int color);
void			get_delta_time();
float			norm_angle(float angle);
int				wall_at(t_vector coordinate);
void			cast(t_ray *ray, int col);
t_ray			new_ray(float ray_angle);
void			render_walls(t_ray ray, int col, t_vector wall_hit, int is_hor_hit);
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
void			*ft_memcpy(void *dst, const void *src, size_t len);
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
void			deletelist(t_lst** head_ref);
t_pair			*make_pair(void *a, void *b);
void	lstiter(t_lst *lst, void *(*f)(void *content));
void			push_front(t_lst** head_ref, t_lst* new);
void	load_image(int i, t_string path, int type);
int		is_out_of_window(t_vector A);
int		shadow(int color, double distance);
void	sort_sprites();
void    show_sprites();
void	update_sprites();
void    *sf_malloc(size_t size);
void    free_all(int status);
int		wall_at(t_vector coordinate);
void		text(char *str, int x, int y, int color);
int 	mouse(int x, int y);
char	*ft_strtrim(char const *s1, char const *set);
/*=========================================================*/
#endif
