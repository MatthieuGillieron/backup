/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_move_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magillie <magillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:34:42 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/18 11:54:13 by magillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include <time.h>

extern t_game	*g_game;

int	cell_is_walkable(char **map, int x, int y)
{
	int	map_h;
	int	map_w;

	map_h = 0;
	map_w = 0;
	if (y < 0)
		return (0);
	while (map[map_h])
		map_h++;
	if (y >= map_h)
		return (0);
	while (map[y][map_w])
		map_w++;
	if (x < 0 || x >= map_w)
		return (0);
	if (map[y][x] == '1')
		return (0);
	if (map[y][x] == 'D' && g_game && g_game->door_states[y][x].open == 0)
		return (0);
	return (1);
}

int	check_area(char **map, t_bounds b)
{
	int	i;
	int	j;

	i = b.min_y;
	while (i <= b.max_y)
	{
		j = b.min_x;
		while (j <= b.max_x)
		{
			if (!cell_is_walkable(map, j, i))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_walkable(char **map, double x, double y)
{
	t_bounds	b;

	b.min_x = (int)(x - PLAYER_RADIUS);
	b.max_x = (int)(x + PLAYER_RADIUS);
	b.min_y = (int)(y - PLAYER_RADIUS);
	b.max_y = (int)(y + PLAYER_RADIUS);
	return (check_area(map, b));
}

void	update_best_position(t_walkable *w, double r)
{
	double	angle;
	double	nx;
	double	ny;
	double	dist;

	angle = 0;
	while (angle < 2 * M_PI)
	{
		nx = w->cx + cos(angle) * r;
		ny = w->cy + sin(angle) * r;
		if (is_walkable(w->map, nx, ny))
		{
			dist = (nx - w->cx) * (nx - w->cx)
				+ (ny - w->cy) * (ny - w->cy);
			if (dist < w->best_dist)
			{
				w->best_dist = dist;
				w->best_x = nx;
				w->best_y = ny;
				w->found = 1;
			}
		}
		angle += M_PI / 16;
	}
}

int	find_nearest_walkable(char **map, double *x, double *y)
{
	t_walkable	w;
	double		r;

	w.map = map;
	w.cx = *x;
	w.cy = *y;
	w.best_dist = DBL_MAX;
	w.found = 0;
	r = 0.1;
	while (r < 2.0 && !w.found)
	{
		update_best_position(&w, r);
		r += 0.1;
	}
	if (w.found)
	{
		*x = w.best_x;
		*y = w.best_y;
		return (1);
	}
	return (0);
}
