/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:09:38 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/18 11:32:56 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static t_img	*select_wall_texture(t_game *game, t_ray_hit *hit, double ray_angle)
{
	if (hit->side == 0)
	{
		if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
			return (&game->textures.west);
		return (&game->textures.east);
	}
	if (ray_angle > 0 && ray_angle < M_PI)
		return (&game->textures.south);
	return (&game->textures.north);
}

static double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

static t_img	*handle_out_of_bounds(t_game *game, t_ray_hit *hit, double ray_angle)
{
	ray_angle = normalize_angle(ray_angle);
	return (select_wall_texture(game, hit, ray_angle));
}

static t_img	*handle_door(t_game *game, t_ray_hit *hit)
{
	if (game->door_states && game->door_states[hit->map_y][hit->map_x].open)
		return (NULL);
	return (&game->textures.door);
}

t_img	*get_wall_texture(t_game *game, t_ray_hit *hit, double ray_angle)
{
	if (hit->map_y < 0 || hit->map_x < 0 ||
		!game->map[hit->map_y] ||
		hit->map_x >= (int)ft_strlen(game->map[hit->map_y]))
		return (handle_out_of_bounds(game, hit, ray_angle));
	if (game->map[hit->map_y][hit->map_x] == 'D')
		return (handle_door(game, hit));
	ray_angle = normalize_angle(ray_angle);
	return (select_wall_texture(game, hit, ray_angle));
}

int	get_texture_color(t_img *texture, int x, int y)
{
	char	*dst;
	int		color;

	if (!texture || !texture->addr)
		return (0);
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}
