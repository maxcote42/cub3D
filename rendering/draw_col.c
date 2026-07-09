/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_col.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 17:56:36 by maxcote           #+#    #+#             */
/*   Updated: 2026/07/07 16:45:42 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	rgb_to_hex_convert(int *rgb)
{
	unsigned int	color;

	color = (rgb[0] << 16) | (rgb[1] << 8) | (rgb[2]);
	return (color);
}

static void	init_draw(t_game *game, t_ray ray, double distance, t_draw *d)
{
	d->nombre = (int)((SCREEN_X / 2.0) / (game->tan_fov * distance));
	d->start = SCREEN_Y / 2 - d->nombre / 2;
	d->end = SCREEN_Y - d->start;
	if (d->start < 0)
		d->start = 0;
	if (d->end > SCREEN_Y)
		d->end = SCREEN_Y - 1;
	if (ray.side == TEXT_NO || ray.side == TEXT_EA)
		d->text_x = (int)(ray.wall_hit * game->text_w[ray.side]);
	else
		d->text_x = game->text_w[ray.side]
			- 1 - (int)(fmod(ray.wall_hit, 1.0) * game->text_w[ray.side]);
	if (d->text_x < 0)
		d->text_x = 0;
	if (d->text_x >= game->text_w[ray.side])
		d->text_x = game->text_w[ray.side] - 1;
}

static int	get_texture_pixel(t_image *tex, int text_x, int text_y, int tex_h)
{
	char	*pixel;

	if (text_y < 0)
		text_y = 0;
	if (text_y >= tex_h)
		text_y = tex_h - 1;
	pixel = tex->addr + (text_y * tex->line_len + text_x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	draw_wall(t_game *game, t_draw *d, t_ray ray, double fog)
{
	int		i;
	double	step;
	double	tex_pos;
	t_image	*tex;
	int		tex_h;

	select_wall_texture(game, ray, &tex, &tex_h);
	step = tex_h / (double)d->nombre;
	tex_pos = (d->start - (SCREEN_Y / 2 - d->nombre / 2)) * step;
	i = d->start;
	while (i <= d->end)
	{
		add_pixel(&game->image, d->col, i, apply_fog(get_texture_pixel(tex,
					d->text_x, (int)tex_pos, tex_h), fog));
		tex_pos += step;
		i++;
	}
}

void	draw_col(t_game *game, int col, double distance, t_ray ray)
{
	t_draw	d;
	int		i;
	double	fog;

	d.col = col;
	if (distance == 0)
		distance = 0.0001;
	fog = get_fog(distance);
	init_draw(game, ray, distance, &d);
	i = 0;
	while (i < d.start)
	{
		add_pixel(&game->image, col, i, game->ceil_fog_table[i]);
		i++;
	}
	draw_wall(game, &d, ray, fog);
	i = d.end + 1;
	while (i < SCREEN_Y)
	{
		add_pixel(&game->image, col, i, game->floor_fog_table[i]);
		i++;
	}
}
