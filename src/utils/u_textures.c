/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:38:35 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/20 21:40:07 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	check_extension(const char *path)
{
	const char	*ext;

	ext = ft_strrchr(path, '.');
	if (!ext || ft_strncmp(ext, ".xpm", 5) != 0)
	{
		print_error("Invalid texture extension", NULL);
		return (0);
	}
	return (1);
}

int	try_load_image(const char *path, void *mlx)
{
	void	*img;
	int		w;
	int		h;

	img = mlx_xpm_file_to_image(mlx, (char *)path, &w, &h);
	if (!img)
	{
		print_error(ERR_TEXTURE_LOAD, NULL);
		return (0);
	}
	mlx_destroy_image(mlx, img);
	return (1);
}
