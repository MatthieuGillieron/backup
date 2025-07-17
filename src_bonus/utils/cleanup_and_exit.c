/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/17 15:23:54 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	cleanup_and_exit(char *error_msg, char **files, t_map_data *map)
{
	int	i;

	if (files)
	{
		i = 0;
		while (files[i])
			free(files[i++]);
		free(files);
	}
	if (map)
		free_map_data(map);
	get_next_line(-42);
	print_error(error_msg, NULL);
}
