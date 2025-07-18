/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_find_walkable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magillie <magillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:15:00 by magillie          #+#    #+#             */
/*   Updated: 2025/07/18 12:18:47 by magillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	find_nearest_walkable(char **map, double *x, double *y)
{
	t_walkable	w;
	double		r;

	w.map = map;
	w.cx = *x;
	w.cy = *y;
	w.best_dist = DBL_MAX;
	w.best_x = *x;
	w.best_y = *y;
	w.found = 0;
	r = 0.05;
	while (r < 1.0)
	{
		update_best_position(&w, r);
		r += 0.05;
	}
	if (w.found)
	{
		*x = w.best_x;
		*y = w.best_y;
		return (1);
	}
	return (0);
}
