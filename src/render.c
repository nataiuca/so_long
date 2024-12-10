/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:06:48 by natferna          #+#    #+#             */
/*   Updated: 2024/12/10 23:29:58 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
