/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:21:17 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 12:22:47 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

#include "../cub3D.h"

static void	init_player(t_game *game)
{
	game->px = game->map->player_x + 0.5;
	game->py = game->map->player_y + 0.5;
	if (game->map->player_dir == 'N')
		game->angle = -M_PI / 2;
	else if (game->map->player_dir == 'S')
		game->angle = M_PI / 2;
	else if (game->map->player_dir == 'E')
		game->angle = 0;
	else if (game->map->player_dir == 'W')
		game->angle = M_PI;
	return ;
}

static int	load_textures(t_game *game, t_text id, char *path)
{
	game->text[id].img = mlx_xpm_file_to_image(game->mlx,
			path, &game->text_w[id], &game->text_h[id]);
	if (!game->text[id].img)
		return (ft_puterr("Failed to load texture"), ERROR);
	game->text[id].addr = mlx_get_data_addr(game->text[id].img,
			&game->text[id].bpp,
			&game->text[id].line_len,
			&game->text[id].endian);
	game->ceil_color = rgb_to_hex_convert(game->map->ceil);
	game->floor_color = rgb_to_hex_convert(game->map->floor);
	return (OK);
}

static int	init_textures(t_game *game)
{
	if (load_textures(game, TEXT_NO, game->map->no) == ERROR
		|| load_textures(game, TEXT_SO, game->map->so) == ERROR
		|| load_textures(game, TEXT_EA, game->map->ea) == ERROR
		|| load_textures(game, TEXT_WE, game->map->we) == ERROR)
		return (ERROR);
	return (OK);
}

int	render(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_puterr("la mlx n'a pas init"),
			free_grid(game->map->grid), ERROR);
	if (init_textures(game) == ERROR || init_hand(game) == false
		|| init_door(game) == ERROR)
		return (ERROR);
	game->win = mlx_new_window(game->mlx, SCREEN_X, SCREEN_Y, NAME);
	if (!game->win)
	{
		ft_puterr("la window n'a pas init");
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		free_grid(game->map->grid);
		return (ERROR);
	}
	game->image.img = mlx_new_image(game->mlx, SCREEN_X, SCREEN_Y);
	game->image.addr = mlx_get_data_addr(game->image.img,
			&game->image.bpp, &game->image.line_len, &game->image.endian);
	init_player(game);
	init_fc_fog_table(game);
	trace(game);
	setup_hooks(game);
	mlx_loop(game->mlx);
	return (OK);
}
