/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:02:23 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 16:29:39 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

# define ERROR -1
# define OK 0

# define SCREEN_X 2560
# define SCREEN_Y 1440
# define NAME "Cube trimadimensionnel"

# define M_PI 3.14159
# define FOV 1.1519
# define SCALE 10
# define STEP 0.2
# define ROT_STEP 0.047600

# define DOOR_PATH "bonus/door.xpm"

# define MAX_MAP_SIZE 500

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <stdint.h>
# include <stdbool.h>
# include <stddef.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef enum e_dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
}	t_dir;

typedef enum e_text
{
	TEXT_NO,
	TEXT_SO,
	TEXT_EA,
	TEXT_WE,
}	t_text;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
}	t_keys;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	**file;
	int		map_start;
	int		fd;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor[3];
	bool	floor_set;
	int		ceil[3];
	bool	ceil_set;
	char	player_dir;
}					t_map;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_camera
{
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}	t_camera;

typedef struct s_ray
{
	double	dirx;
	double	diry;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	double	nextx;
	double	nexty;
	double	deltax;
	double	deltay;
	int		side;
	double	perpwalldist;
	double	wall_hit;
}					t_ray;

typedef struct s_draw
{
	int		col;
	int		start;
	int		end;
	int		text_x;
	int		nombre;
}	t_draw;

# define HAND_BACK 0xFF00FF
# define HAND_FRAMES 5
# define HAND_SPEED 8
# define FOG_DIST_MAX 6.0
# define FOG_MIN 0.15

typedef struct s_game
{
	t_map			*map;
	void			*mlx;
	void			*win;
	t_image			image;
	int				height;
	int				width;
	double			px;
	double			py;
	double			angle;
	int				moves;
	t_image			text[4];
	int				text_w[4];
	int				text_h[4];

	t_image			door_tex;
	int				door_w;
	int				door_h;

	t_image			hand[HAND_FRAMES];
	int				hand_w[HAND_FRAMES];
	int				hand_h[HAND_FRAMES];
	int				hand_frame;
	int				hand_count;

	int				mouse_x;

	unsigned int	ceil_color;
	unsigned int	floor_color;
	t_keys			keys;
	double			tan_fov;
	unsigned int	ceil_fog_table[SCREEN_Y];
	unsigned int	floor_fog_table[SCREEN_Y];
}					t_game;

// utils1.c
int		read_line(int fd, char **tmp);
bool	ft_puterr(char *str);

// utils/memory.c
bool	free_grid(char **grid);
bool	free_map(t_map *map);

// utils/correct_char.c (mandatory) / bonus/correct_char_bonus.c (bonus)
int		correct_char(char c, t_map *map, int y, int x);

// utils/reach_wall.c (mandatory) / bonus/reach_wall_bonus.c (bonus)
bool	reach_wall(t_game *game, int map_x, int map_y);

// utils/move.c (mandatory) / bonus/move_bonus.c (bonus)
void	safe_move(t_game *game, double nx, double ny);

// color_utils.c
bool	set_color(t_map *map, char *str, bool is_floor);

// hook_utils.c
void	set_key_state(int keycode, t_game *game, bool state);
void	get_move_vector(t_game *game, double *dx, double *dy);
void	apply_rotation(t_game *game);

// parsing/parsing.c
bool	correct_extension(char *str);
bool	valid_map(char *av, t_map *map);
int		parse(int ac, char **av, t_map *map);

// parsing/parse_file.c
bool	read_file(t_map *map, char *path);
bool	read_map(t_map *map);

// parsing/parse_header.c
bool	boring_check(char *str);
void	parse_color(char *str, int *rgb);
bool	valid_rgb(int r, int g, int b);
bool	is_valid_color_str(char *str);
bool	set_texture_path(char **field, char *str, int offset);
bool	parse_header(t_map *map);

// parsing/parse_map.c
bool	correct_elements(t_map *map);
bool	is_valid_neighbor(t_map *map, int x, int y);
bool	is_enclosed(t_map *map);
bool	pad_grid(t_map *map);

// rendering/rendering.c
int		rgb_to_hex_convert(int *rgb);
int		render(t_game *game);
void	trace(t_game *game);
void	add_pixel(t_image *img, int x, int y, int color);
void	trace_3d(t_game *game);
int		handle_cross(t_game *game);
void	draw_col(t_game *game, int col, double distance, t_ray ray);
void	setup_hooks(t_game *game);

// rendering/run_dda.c
double	run_dda(t_game *game, t_ray *ray);

// rendering/fog.c
double	get_fog(double distance);
int		apply_fog(int color, double fog);
double	get_fc_fog(int i);
void	init_fc_fog_table(t_game *game);

void	select_wall_texture(t_game *game, t_ray ray, t_image **tex,
			int *tex_h);
void	trace_minimap(t_game *game);
bool	init_hand(t_game *game);
void	update_hand_anim(t_game *game);
void	draw_hand(t_game *game);
void	toggle_door(t_game *game);
int		init_door(t_game *game);
void	free_bonus_resources(t_game *game);
void	setup_bonus_hooks(t_game *game);

#endif