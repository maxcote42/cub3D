/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:02:29 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/03 17:14:59 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	game.map = malloc(sizeof(t_map));
	if (!game.map)
		return (ERROR);
	ft_bzero(game.map, sizeof(t_map));
	if (parse(ac, av, game.map) == ERROR)
		return (free_map(game.map), ERROR);
	if (render(&game) == ERROR)
	{
		free_map(game.map);
		return (ERROR);
	}
	free_map(game.map);
	return (OK);
}
