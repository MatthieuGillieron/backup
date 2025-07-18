/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_window.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:18:49 by mg                #+#    #+#             */
/*   Updated: 2025/07/18 11:29:18 by mg               ###   ########.fr       */
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

static int	get_door_coords(t_game *game, int *tx, int *ty)
{
	double	px;
	double	py;
	double	dx;
	double	dy;
	double	step;

	px = game->player.x;
	py = game->player.y;
	dx = cos(game->player.angle);
	dy = sin(game->player.angle);
	step = 0.5;
	*tx = (int)(px + dx * step);
	*ty = (int)(py + dy * step);
	if (*tx < 0 || *ty < 0 || !game->map[*ty])
		return (0);
	if (*tx >= (int)ft_strlen(game->map[*ty]))
		return (0);
	return (1);
}

static void	try_open_door(t_game *game)
{
	int	tx;
	int	ty;

	if (!get_door_coords(game, &tx, &ty))
		return ;
	if (game->map[ty][tx] == 'D' && game->door_states[ty][tx].open == 0)
	{
		game->door_states[ty][tx].open = 1;
		game->door_states[ty][tx].open_time = time(NULL);
		game->map[ty][tx] = '0';
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
		game->keys.left = 1;
	else if (keycode == KEY_D)
		game->keys.right = 1;
	else if (keycode == KEY_LEFT)
		game->keys.rotate_left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.rotate_right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.forward = 0;
	else if (keycode == KEY_S)
		game->keys.backward = 0;
	else if (keycode == KEY_A)
		game->keys.left = 0;
	else if (keycode == KEY_D)
		game->keys.right = 0;
	else if (keycode == KEY_LEFT)
		game->keys.rotate_left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.rotate_right = 0;
	else if (keycode == KEY_SPACE)
		try_open_door(game);
	return (0);
}
