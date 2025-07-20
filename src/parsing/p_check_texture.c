/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_check_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:45:11 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/20 21:38:15 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	is_valid_texture(const char *path, void *mlx)
{
	int		fd;
	char	*new_path;
	int		result;

	new_path = ft_strtrim(path, " \t\n");
	fd = open(new_path, O_RDONLY);
	if (fd < 0)
	{
		free(new_path);
		return (0);
	}
	close(fd);
	if (!check_extension(new_path))
	{
		free(new_path);
		return (0);
	}
	result = try_load_image(new_path, mlx);
	free(new_path);
	return (result);
}

int	check_path(t_map_data *data, void *mlx_ptr)
{
	if (!is_valid_texture(data->textures.no, mlx_ptr))
		return (0);
	if (!is_valid_texture(data->textures.so, mlx_ptr))
		return (0);
	if (!is_valid_texture(data->textures.we, mlx_ptr))
		return (0);
	if (!is_valid_texture(data->textures.ea, mlx_ptr))
		return (0);
	return (1);
}

static void	validate_map_enclosure(char **files, t_map_data *map)
{
	int	result;

	result = is_map_enclosed(map->map, &map->player);
	if (result == -1)
		cleanup_and_exit(ERR_MAP_INVALID_CHAR, files, map);
	if (result == -2)
		cleanup_and_exit(ERR_MAP_MULTI_PLAYER, files, map);
	if (result == 0)
		cleanup_and_exit(ERR_MAP_NOT_ENCLOSED, files, map);
}

static void	validate_mlx_and_resources(char **files, t_map_data *map)
{
	void	*mlx;

	mlx = mlx_init();
	if (!check_path(map, mlx))
	{
		//mlx_destroy_display(mlx);
		free(mlx);
		cleanup_and_exit(ERR_TEXTURE_PATH, files, map);
	}
	if (!parse_colors(map))
	{
		//mlx_destroy_display(mlx);
		free(mlx);
		cleanup_and_exit(ERR_RGB_FORMAT, files, map);
	}
	assign_direction(&map->player);
	//mlx_destroy_display(mlx);
	free(mlx);
}

int	check_file(char **files, t_map_data *map)
{
	if (!split_sections(files, map))
		return (1);
	validate_map_enclosure(files, map);
	validate_mlx_and_resources(files, map);
	return (0);
}
