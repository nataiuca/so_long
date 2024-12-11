/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 21:10:24 by natferna          #+#    #+#             */
/*   Updated: 2024/12/10 23:28:27 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdio.h>
#include <stdlib.h>

int	is_valid_move(t_game *game, int x, int y, int **visited)
{
	return (x >= 0 && x < game->width && y >= 0 && y < game->height
		&& !visited[y][x] && game->map[y][x] != '1');
}

void	handle_collectible(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'C')
		game->collected++;
}

void	find_exit_position(char **map, t_game *game, int *exit_x, int *exit_y)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (map[y][x] == 'E')
			{
				*exit_x = x;
				*exit_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	mark_exit_as_wall(char **map, t_game *game)
{
	int	exit_x;
	int	exit_y;

	exit_x = game->player_x;
	exit_y = game->player_y;
	find_exit_position(map, game, &exit_x, &exit_y);
	map[exit_y][exit_x] = '1';
}

int	exit_game_wrapper(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	exit_game(game);
	return (0);
}

