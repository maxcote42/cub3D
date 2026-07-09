/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 01:43:02 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/06/18 17:50:37 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	boring_check(char *str)
{
	if (ft_strncmp(str, "NO ", 3) == 0)
		return (true);
	if (ft_strncmp(str, "SO ", 3) == 0)
		return (true);
	if (ft_strncmp(str, "WE ", 3) == 0)
		return (true);
	if (ft_strncmp(str, "EA ", 3) == 0)
		return (true);
	if (ft_strncmp(str, "F ", 2) == 0)
		return (true);
	if (ft_strncmp(str, "C ", 2) == 0)
		return (true);
	return (false);
}

bool	set_texture_path(char **field, char *str, int offset)
{
	if (*field != NULL)
		return (ft_puterr("Duplicate texture identifier"));
	while (str[offset] == ' ')
		offset++;
	if (str[offset] == '\0')
		return (ft_puterr("Empty texture path"));
	*field = ft_strdup(str + offset);
	if (*field == NULL)
		return (false);
	return (true);
}

bool	set_textures_path(char *str, t_map *map)
{
	if (ft_strncmp(str, "NO ", 3) == 0)
		return (set_texture_path(&map->no, str, 3));
	if (ft_strncmp(str, "SO ", 3) == 0)
		return (set_texture_path(&map->so, str, 3));
	if (ft_strncmp(str, "WE ", 3) == 0)
		return (set_texture_path(&map->we, str, 3));
	if (ft_strncmp(str, "EA ", 3) == 0)
		return (set_texture_path(&map->ea, str, 3));
	if (ft_strncmp(str, "F ", 2) == 0)
		return (set_color(map, str, true));
	if (ft_strncmp(str, "C ", 2) == 0)
		return (set_color(map, str, false));
	return (true);
}

bool	is_line_blank(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool	parse_header(t_map *map)
{
	int	i;

	i = 0;
	while (map->file[i])
	{
		if (boring_check(map->file[i]) == true)
		{
			if (set_textures_path(map->file[i], map) == false)
				return (false);
		}
		else if (is_line_blank(map->file[i]) == true)
			;
		else if (map->file[i][0] != '\n' && map->file[i][0] != '\0')
		{
			map->map_start = i;
			if (!map->no || !map->so || !map->we || !map->ea
				|| !map->floor_set || !map->ceil_set)
				return (ft_puterr("Missing header element"));
			return (true);
		}
		i++;
	}
	return (ft_puterr("No map found"));
}
