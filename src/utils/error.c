/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/15 22:57:10 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	print_error(char *error_msg, t_game *game)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
	if (game)
		close_window(game);
	else
		exit(1);
}
