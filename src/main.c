/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/16 10:29:49 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	free_files(char **files)
{
	int	i;

	i = 0;
	while (files[i])
		free(files[i++]);
	free(files);
}

static void	setup_game_data(t_game *game, t_map_data *map)
{
	game->map_data = *map;
	game->color.set_floor = map->colors.set_floor;
	game->color.set_ceiling = map->colors.set_ceiling;
	game->player = map->player;
	game->map = map->map;
}

void	game_setup(int ac, char **av, t_game *game)
{
	char		**files;
	t_map_data	map;

	ft_bzero(&map, sizeof(map));
	ft_bzero(game, sizeof(*game));
	if (ac != 2)
		print_error(ERR_ARGS, NULL);
	files = open_map(av[1]);
	if (!files)
		print_error(ERR_MAP_OPEN, NULL);
	if (check_file(files, &map))
	{
		get_next_line(-42);
		free_files(files);
		exit(1);
	}
	free_files(files);
	setup_game_data(game, &map);
	if (!init_game(game))
		print_error(ERR_MLX_INIT, game);
}

void	game_loop(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx, render_loop, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;

	game_setup(ac, av, &game);
	game_loop(&game);
	return (0);
}