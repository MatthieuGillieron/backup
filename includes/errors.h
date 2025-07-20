/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/20 23:01:06 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_ARGS "Usage: ./cub3d <map.cub>"
# define ERR_MAP_EXT "Map file must have .cub extension"
# define ERR_MAP_OPEN "Cannot open map file"
# define ERR_MAP_READ "Cannot read map file"
# define ERR_MAP_EMPTY "Map file is empty"
# define ERR_MAP_INVALID "Invalid map format"
# define ERR_MAP_NOT_ENCLOSED "Map is not enclosed by walls"
# define ERR_MAP_NO_PLAYER "No player found in map"
# define ERR_MAP_MULTI_PLAYER "Multiple players found in map"
# define ERR_TEXTURE_PATH "Invalid texture path"
# define ERR_TEXTURE_LOAD "Cannot load texture file"
# define ERR_TEXTURE_MISSING "Missing texture configuration"
# define ERR_RGB_FORMAT "Invalid RGB color format (R,G,B)"
# define ERR_RGB_RANGE "RGB values must be between 0-255"
# define ERR_RGB_MISSING "Missing floor or ceiling color"
# define ERR_MALLOC "Memory allocation failed"
# define ERR_MLX_INIT "MLX initialization failed"
# define ERR_WIN_CREATE "Window creation failed"
# define ERR_IMG_CREATE "Image creation failed"
# define ERR_MAP_EXTRA_INFO "Map parsing failed: unknown \
or extra information in header"
# define ERR_MAP_INVALID_CHAR "Invalid character \
in map (allowed: 0, 1, N, S, E, W, space)"
# define ERR_MAP_MISSING_SECTION "Map is missing a \
required section (NO, SO, WE, EA, F, C)"
# define ERR_MAP_EXTRA_SECTION "Map has extra or unknown section(s) in header"

#endif