/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:06:48 by natferna          #+#    #+#             */
/*   Updated: 2024/12/07 23:53:43 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_map(t_game *game)
{
	int x, y;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			// ft_printf("Rendering tile at (%d, %d) with value: %c\n", x, y, game->map[y][x]);
			// Asegúrate de que el mapa no sea NULL y que las coordenadas estén dentro del rango
			if (game->map != NULL && game->map[y] != NULL)
			{
				if (game->map[y][x] == '1')
					mlx_put_image_to_window(game->mlx, game->win,
						game->wall_img, x * TILE_SIZE, y * TILE_SIZE);
				else if (game->map[y][x] == 'P')
					mlx_put_image_to_window(game->mlx, game->win,
						game->player_img, x * TILE_SIZE, y * TILE_SIZE);
				else if (game->map[y][x] == 'C')
					mlx_put_image_to_window(game->mlx, game->win,
						game->collectible_img, x * TILE_SIZE, y * TILE_SIZE);
				else if (game->map[y][x] == 'E')
					mlx_put_image_to_window(game->mlx, game->win,
						game->exit_img, x * TILE_SIZE, y * TILE_SIZE);
				else if (game->map[y][x] == '0')
					mlx_put_image_to_window(game->mlx, game->win,
						game->empty_img, x * TILE_SIZE, y * TILE_SIZE);
			}
			x++;
		}
		y++;
	}
}
