/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_move_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magillie <magillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:57:11 by mg                #+#    #+#             */
/*   Updated: 2025/07/18 12:15:30 by magillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	move_player_no_collision(t_game *game,
	double new_x, double new_y, double *moved)
{
	if (!is_walkable(game->map, game->player.x, game->player.y))
	{
		if (find_nearest_walkable(game->map,
				&game->player.x, &game->player.y))
			game->collision_active = 1;
		return ;
	}
	if (cell_is_walkable(game->map, (int)new_x, (int)game->player.y))
	{
		game->player.x = new_x;
		*moved = 1;
	}
	if (cell_is_walkable(game->map, (int)game->player.x, (int)new_y))
	{
		game->player.y = new_y;
		*moved = 1;
	}
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	moved;

	new_x = game->player.x + cos(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle) * MOVE_SPEED;
	moved = 0;
	if (!game->collision_active)
		move_player_no_collision(game, new_x, new_y, &moved);
	else
	{
		if (is_walkable(game->map, new_x, game->player.y)
			&& game->map[(int)game->player.y][(int)new_x] != '1')
			game->player.x = new_x;
		if (is_walkable(game->map, game->player.x, new_y)
			&& game->map[(int)new_y][(int)game->player.x] != '1')
			game->player.y = new_y;
	}
	if (moved)
		game->collision_active = 1;
}

static void	move_player_no_collision_back(t_game *game,
	double new_x, double new_y, double *moved)
{
	if (!is_walkable(game->map, game->player.x, game->player.y))
	{
		if (find_nearest_walkable(game->map,
				&game->player.x, &game->player.y))
			game->collision_active = 1;
		return ;
	}
	if (cell_is_walkable(game->map, (int)new_x, (int)game->player.y))
	{
		game->player.x = new_x;
		*moved = 1;
	}
	if (cell_is_walkable(game->map, (int)game->player.x, (int)new_y))
	{
		game->player.y = new_y;
		*moved = 1;
	}
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	moved;

	new_x = game->player.x - cos(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y - sin(game->player.angle) * MOVE_SPEED;
	moved = 0;
	if (!game->collision_active)
		move_player_no_collision_back(game, new_x, new_y, &moved);
	else
	{
		if (is_walkable(game->map, new_x, game->player.y)
			&& game->map[(int)game->player.y][(int)new_x] != '1')
			game->player.x = new_x;
		if (is_walkable(game->map, game->player.x, new_y)
			&& game->map[(int)new_y][(int)game->player.x] != '1')
			game->player.y = new_y;
	}
	if (moved)
		game->collision_active = 1;
}
