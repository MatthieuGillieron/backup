/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:18:49 by mg                #+#    #+#             */
/*   Updated: 2025/07/18 11:29:29 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	update_movement(t_game *game)
{
	if (game->keys.forward)
		move_forward(game);
	if (game->keys.backward)
		move_backward(game);
	if (game->keys.left)
		move_left(game);
	if (game->keys.right)
		move_right(game);
	if (game->keys.rotate_left)
		rotate_player(game, -1);
	if (game->keys.rotate_right)
		rotate_player(game, 1);
}

int	mouse_motion(int x, int y, t_game *game)
{
	static int	last_x = -1;
	int			dx;

	if (last_x != -1)
	{
		dx = x - last_x;
		game->player.angle += dx * MOUSE_SENS;
		if (game->player.angle >= 2 * M_PI)
			game->player.angle -= 2 * M_PI;
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
	}
	last_x = x;
	(void)y;
	return (0);
}
