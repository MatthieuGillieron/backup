/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_valid_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:27:39 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/20 23:58:09 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	is_valid_surrounding(char **map, int y, int x)
{
	int	len_up;
	int	len_down;
	int	len_curr;

	if (!is_playable(map[y][x]) && !is_door(map[y][x]))
		return (1);
	if (y == 0 || x == 0)
		return (0);
	if (!map[y - 1] || !map[y + 1])
		return (0);
	len_curr = ft_strlen(map[y]);
	len_up = ft_strlen(map[y - 1]);
	len_down = ft_strlen(map[y + 1]);
	if (x >= len_curr || x >= len_up || x >= len_down)
		return (0);
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' ||
		map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (0);
	return (1);
}

static int	check_map_char(char *line, int j, int y, t_map_ctx *ctx)
{
	if (line[j] != '0' && line[j] != '1' && line[j] != 'D' && line[j] != '\n' \
		&& !is_player(line[j]) && line[j] != ' ')
	{
		cleanup_and_exit(ERR_MAP_INVALID_CHAR, ctx->files, ctx->map_data);
		return (0);
	}
	if (is_player(line[j]))
	{
		ctx->info->player_count++;
		ctx->info->player->x = j;
		ctx->info->player->y = y;
		ctx->info->player->direction = line[j];
	}
	if (!is_valid_surrounding(ctx->map, y, j))
		return (0);
	return (1);
}

static int	check_map_characters(char *line, int y, t_map_ctx *ctx)
{
	int	j;
	int	len_line;

	len_line = ft_strlen(line);
	j = 0;
	while (j < len_line)
	{
		if (!check_map_char(line, j, y, ctx))
			return (0);
		j++;
	}
	return (1);
}

int	check_map_line(char *line, int y, t_map_ctx *ctx)
{
	int			len_line;
	int			last_index;

	len_line = check_line(line, &last_index);
	if (!check_map_characters(line, y, ctx))
		return (0);
	if (last_index >= 0 && (last_index + 1 >= len_line \
		|| (line[last_index + 1] != '1' && line[last_index + 1] != 'D')))
		return (0);
	return (1);
}

int	is_map_enclosed(char **map, t_player *player, \
	char **files, t_map_data *map_data)
{
	int			i;
	t_map_check	info;
	t_map_ctx	ctx;

	i = 0;
	info.player = player;
	info.player_count = 0;
	ctx.map = map;
	ctx.info = &info;
	ctx.files = files;
	ctx.map_data = map_data;
	while (map[i])
	{
		if (!check_map_line(map[i], i, &ctx))
			return (0);
		i++;
	}
	if (info.player_count > 1)
		return (-1);
	return (info.player_count == 1);
}
