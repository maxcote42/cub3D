/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:06:44 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 03:09:58 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	correct_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len <= 4)
		return (false);
	if (ft_strncmp(str + len - 4, ".cub", 4) != 0)
		return (false);
	if (ft_strnstr(str, ".cub", len - 4) != NULL)
		return (false);
	return (true);
}

bool	valid_map(char *av, t_map *map)
{
	if (read_file(map, av) == false)
		return (ft_puterr("Failed to read map file"));
	if (parse_header(map) == false)
		return (false);
	if (read_map(map) == false)
		return (ft_puterr("Failed to load map grid"));
	if (pad_grid(map) == false)
		return (false);
	free_grid(map->file);
	map->file = NULL;
	if (is_enclosed(map) == false)
		return (false);
	if (correct_elements(map) == false)
		return (false);
	return (true);
}

int	parse(int ac, char **av, t_map *map)
{
	if (ac != 2)
		return (ft_puterr("Usage: ./cub3D map.cub"), ERROR);
	if (correct_extension(av[1]) == false)
		return (ft_puterr("Invalid file extension"), ERROR);
	if (valid_map(av[1], map) == false)
		return (ERROR);
	return (OK);
}
