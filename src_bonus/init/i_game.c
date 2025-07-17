/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_game.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:35:38 by mg                #+#    #+#             */
/*   Updated: 2025/07/17 16:22:08 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include <stdlib.h>
#include <time.h>

static void init_door_states(t_game *game)
{
	int h = 0, w = 0, i, j;
	while (game->map[h]) h++;
	while (game->map[0][w]) w++;
	game->door_states = malloc(sizeof(t_door_state*) * h);
	for (i = 0; i < h; i++) {
		game->door_states[i] = malloc(sizeof(t_door_state) * w);
		for (j = 0; j < w; j++) {
			game->door_states[i][j].open = 0;
			game->door_states[i][j].open_time = 0;
		}
	}
}

int	init_game(t_game *game)
{
	game->win_w = 640;
	game->win_h = 480;
	game->map = game->map_data.map;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "cub3D");
	if (!game->win)
		return (0);
	if (!load_textures(game))
		return (0);
	init_door_states(game);
	return (1);
}
