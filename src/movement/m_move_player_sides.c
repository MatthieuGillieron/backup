/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_move_player_sides.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:30:15 by magillie          #+#    #+#             */
/*   Updated: 2025/07/18 17:34:45 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	moved;

	new_x = game->player.x + cos(game->player.angle - M_PI / 2) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle - M_PI / 2) * MOVE_SPEED;
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

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	moved;

	new_x = game->player.x + cos(game->player.angle + M_PI / 2) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle + M_PI / 2) * MOVE_SPEED;
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
