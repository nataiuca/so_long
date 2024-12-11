/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:05:54 by natferna          #+#    #+#             */
/*   Updated: 2024/12/11 10:48:19 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	load_image(t_game *game, char *file, void **img)
{
	*img = mlx_xpm_file_to_image(game->mlx, file, \
	&game->img_width, &game->img_height);
	return (*img != NULL);
}

int	print_image_loaded(char *image_name)
{
	ft_printf("%s loaded\n", image_name);
	return (1);
}

int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->width * \
	TILE_SIZE, game->height * TILE_SIZE, "So Long");
	if (!game->win)
		return (0);
	if (!load_image(game, "images/wall.xpm", &game->wall_img) \
		|| !load_image(game, "images/player.xpm", &game->player_img) \
		|| !load_image(game, "images/exit.xpm", &game->exit_img) \
		|| !load_image(game, "images/collectible.xpm", &game->collectible_img) \
		|| !load_image(game, "images/empty.xpm", &game->empty_img))
		return (0);
	print_image_loaded("wall");
	print_image_loaded("player");
	print_image_loaded("exit");
	print_image_loaded("collectible");
	print_image_loaded("empty");
	return (1);
}

void	handle_events(t_game *game)
{
	mlx_key_hook(game->win, handle_key, game);
	mlx_hook(game->win, 17, 0, exit_game_wrapper, game);
	mlx_loop(game->mlx);
}

void	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	free_map(game->map);
	exit(0);
}
