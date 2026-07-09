/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfeijoei <sfeijoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:14:29 by sfeijoei          #+#    #+#             */
/*   Updated: 2026/07/07 12:14:43 by sfeijoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	select_wall_texture(t_game *game, t_ray ray, t_image **tex,
		int *tex_h)
{
	*tex = &game->text[ray.side];
	*tex_h = game->text_h[ray.side];
}
