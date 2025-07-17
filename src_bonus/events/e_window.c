/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_window.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:06:51 by mg                #+#    #+#             */
/*   Updated: 2025/07/17 17:03:22 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include <time.h>

int	close_window(t_game *game)
{
	free_map_data(&game->map_data);
	free_door_states(game->door_states, game->map);
	if (game->textures.north.img)
		mlx_destroy_image(game->mlx, game->textures.north.img);
	if (game->textures.south.img)
		mlx_destroy_image(game->mlx, game->textures.south.img);
	if (game->textures.east.img)
		mlx_destroy_image(game->mlx, game->textures.east.img);
	if (game->textures.west.img)
		mlx_destroy_image(game->mlx, game->textures.west.img);
	if (game->textures.door.img)
		mlx_destroy_image(game->mlx, game->textures.door.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}

static void try_open_door(t_game *game)
{
	double px = game->player.x;
	double py = game->player.y;
	double dx = cos(game->player.angle);
	double dy = sin(game->player.angle);
	double step = 0.5; // half-tile step forward
	int tx = (int)(px + dx * step);
	int ty = (int)(py + dy * step);
	if (tx < 0 || ty < 0 || !game->map[ty] || tx >= (int)ft_strlen(game->map[ty]))
		return;
	if (game->map[ty][tx] == 'D' && game->door_states[ty][tx].open == 0) {
		game->door_states[ty][tx].open = 1;
		game->door_states[ty][tx].open_time = time(NULL);
		game->map[ty][tx] = '0'; // Mark as open in the map
		printf("Door at (%d, %d) opened!\n", tx, ty);
	}
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		game->keys.forward = 1;
	else if (keycode == KEY_S)
		game->keys.backward = 1;
	else if (keycode == KEY_A)
	{
		game->keys.rotate_left = 1;
		rotate_player(game, -1);
	}
	else if (keycode == KEY_D)
	{
		game->keys.rotate_right = 1;
		rotate_player(game, 1);
	}
	else if (keycode == KEY_LEFT)
	{
		game->keys.rotate_left = 1;
		rotate_player(game, -1);
	}
	else if (keycode == KEY_RIGHT)
	{
		game->keys.rotate_right = 1;
		rotate_player(game, 1);
	}
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.forward = 0;
	else if (keycode == KEY_S)
		game->keys.backward = 0;
	else if (keycode == KEY_A)
		game->keys.rotate_left = 0;
	else if (keycode == KEY_D)
		game->keys.rotate_right = 0;
	else if (keycode == KEY_SPACE)
		try_open_door(game);
	return (0);
}

void	update_movement(t_game *game)
{
	if (game->keys.forward)
		move_forward(game);
	if (game->keys.backward)
		move_backward(game);
	if (game->keys.left)
		rotate_player(game, -1);
	if (game->keys.right)
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
