/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A7_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:56:25 by natferna          #+#    #+#             */
/*   Updated: 2024/12/18 19:56:25 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->width * \
	TILE_SIZE, game->height * TILE_SIZE, "So Long");
	if (!game->win)
		return (0);
	if (!load_image(game, "images/wall.xpm", &game->wall_img,"wall") \
		|| !load_image(game, "images/player.xpm", &game->player_img,"player") \
		|| !load_image(game, "images/exit.xpm", &game->exit_img,"exit") \
		|| !load_image(game, "images/collectible.xpm", &game->collectible_img,"collectible") \
		|| !load_image(game, "images/empty.xpm", &game->empty_img,"empty"))
		return (0);
	return (1);
}
void	render_map(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->height)
	{
		y++;
	}
	y = 0;
	while (y < game->height)
	{
		render_row(game, y);
		y++;
	}
}
void	render_tile(t_game *game, int x, int y)
{
	void	*img;

	img = NULL;
	if (game->map[y][x] == '1')
		img = game->wall_img;
	else if (game->map[y][x] == 'P')
		img = game->player_img;
	else if (game->map[y][x] == 'C')
	{
		img = game->collectible_img;
	}
	else if (game->map[y][x] == 'E')
		img = game->exit_img;
	else if (game->map[y][x] == '0')
		img = game->empty_img;
	if (img != NULL)
		mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y
			* TILE_SIZE);
}
void	render_row(t_game *game, int y)
{
	int	x;

	x = 0;
	while (x < game->width)
	{
		if (game->map != NULL && game->map[y] != NULL)
			render_tile(game, x, y);
		x++;
	}
}
void    close_game(t_game *game,char *message)
{
    ft_printf("%s\n", message);
	clean_game(game);
	exit(0);
}