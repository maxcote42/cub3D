/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 03:03:33 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 12:18:07 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

#include "../cub3D.h"

int	init_door(t_game *game)
{
	game->door_tex.img = mlx_xpm_file_to_image(game->mlx,
			DOOR_PATH, &game->door_w, &game->door_h);
	if (!game->door_tex.img)
		return (ft_puterr("Failed to load door texture"), ERROR);
	game->door_tex.addr = mlx_get_data_addr(game->door_tex.img,
			&game->door_tex.bpp, &game->door_tex.line_len,
			&game->door_tex.endian);
	return (OK);
}

static bool	get_target_cell(t_game *game, int *tx, int *ty)
{
	double	fx;
	double	fy;

	fx = game->px + cos(game->angle);
	fy = game->py + sin(game->angle);
	*tx = (int)fx;
	*ty = (int)fy;
	if (*tx == (int)game->px && *ty == (int)game->py)
		return (false);
	return (true);
}

void	toggle_door(t_game *game)
{
	int		tx;
	int		ty;
	char	*cell;

	if (!get_target_cell(game, &tx, &ty))
		return ;
	if (ty < 0 || ty >= game->map->height
		|| tx < 0 || tx >= game->map->width)
		return ;
	cell = &game->map->grid[ty][tx];
	if (*cell == '2')
		*cell = '3';
	else if (*cell == '3')
		*cell = '2';
}
