/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:05:54 by natferna          #+#    #+#             */
/*   Updated: 2024/12/07 23:48:44 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->width * TILE_SIZE, game->height
			* TILE_SIZE, "So Long");
	if (!game->win)
		return (0);
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "images/wall.xpm",
			&game->img_width, &game->img_height);
			ft_printf("%s\n", "wall loaded");
	game->player_img = mlx_xpm_file_to_image(game->mlx, "images/player.xpm",
			&game->img_width, &game->img_height);
			ft_printf("%s\n", "player loaded");
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "images/exit.xpm",
			&game->img_width, &game->img_height);
			ft_printf("%s\n", "exit loaded");
	game->collectible_img = mlx_xpm_file_to_image(game->mlx, "images/collectible.xpm",
			&game->img_width, &game->img_height);
			ft_printf("%s\n", "collectible loaded");
	game->empty_img = mlx_xpm_file_to_image(game->mlx, "images/empty.xpm",
			&game->img_width, &game->img_height);
			ft_printf("%s\n", "empty loaded");
	if (!game->wall_img || !game->player_img || !game->exit_img
		|| !game->collectible_img || !game->empty_img)
	{
		ft_printf("Error: Could not load images\n");
		return (0);
	}
	return (1);
}
