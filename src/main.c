/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/15 22:08:29 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

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
		free_files(files);
		print_error(ERR_MAP_INVALID, NULL);
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
