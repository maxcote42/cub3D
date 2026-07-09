/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:57:45 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 12:22:06 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*extract_line(char *tmp)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!tmp || tmp[0] == '\0')
		return (NULL);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, tmp, i);
	line[i] = '\0';
	return (line);
}

char	*clean_tmp(char *tmp)
{
	size_t	i;
	char	*new;

	if (!tmp)
		return (NULL);
	i = 0;
	while (tmp[i] != '\0' && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		i++;
	if (!tmp[i])
		return (free(tmp), NULL);
	new = ft_strdup(tmp + i);
	if (!new)
		return (free(tmp), NULL);
	free(tmp);
	return (new);
}

int	read_line(int fd, char **tmp)
{
	char	buf[BUFFER_SIZE + 1];
	int		stock;
	char	*join;

	stock = 1;
	while (stock > 0 && !ft_strchr(*tmp, '\n'))
	{
		stock = read(fd, buf, BUFFER_SIZE);
		if (stock < 0)
			return (ERROR);
		buf[stock] = '\0';
		join = ft_strdup(*tmp);
		if (!join)
			return (ERROR);
		free(*tmp);
		*tmp = malloc(ft_strlen(join) + stock + 1);
		if (!*tmp)
			return (free(join), ERROR);
		ft_memcpy(*tmp, join, ft_strlen(join));
		ft_memcpy(*tmp + ft_strlen(join), buf, stock + 1);
		free(join);
	}
	return (stock);
}

bool	ft_puterr(char *str)
{
	int	i;

	i = 0;
	write(2, "Error\n", 6);
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (false);
}
