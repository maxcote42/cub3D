/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 17:42:44 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/06/18 20:51:44 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	parse_color(char *str, int *rgb)
{
	str = str + 2;
	rgb[0] = ft_atoi(str);
	while (*str && *str != ',' && *str != '\n')
		str++;
	if (*str != ',')
	{
		rgb[1] = -1;
		rgb[2] = -1;
		return ;
	}
	str++;
	rgb[1] = ft_atoi(str);
	while (*str && *str != ',' && *str != '\n')
		str++;
	if (*str != ',')
	{
		rgb[2] = -1;
		return ;
	}
	str++;
	rgb[2] = ft_atoi(str);
}

bool	valid_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255)
		return (false);
	if (g < 0 || g > 255)
		return (false);
	if (b < 0 || b > 255)
		return (false);
	return (true);
}

bool	skip_component(char **str)
{
	int	digits;

	digits = 0;
	while (**str >= '0' && **str <= '9')
	{
		if (++digits > 3)
			return (false);
		(*str)++;
	}
	return (digits > 0);
}

bool	is_valid_color_str(char *str)
{
	int	components;

	components = 0;
	while (*str)
	{
		while (*str == ' ')
			str++;
		if (!skip_component(&str))
			return (false);
		components++;
		while (*str == ' ')
			str++;
		if (*str == ',')
			str++;
		else if (*str != '\0')
			return (false);
	}
	return (components == 3);
}

bool	set_color(t_map *map, char *str, bool is_floor)
{
	int		rgb[3];
	bool	*set;
	int		*color;

	if (is_floor)
	{
		set = &map->floor_set;
		color = map->floor;
	}
	else
	{
		set = &map->ceil_set;
		color = map->ceil;
	}
	if (*set)
		return (ft_puterr("Duplicate color identifier"));
	if (!is_valid_color_str(str + 2))
		return (ft_puterr("Invalid color format"));
	parse_color(str, rgb);
	if (!valid_rgb(rgb[0], rgb[1], rgb[2]))
		return (ft_puterr("Color value out of range [0,255]"));
	color[0] = rgb[0];
	color[1] = rgb[1];
	color[2] = rgb[2];
	return (*set = true, true);
}
