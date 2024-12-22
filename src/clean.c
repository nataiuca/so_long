/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:04:43 by natferna          #+#    #+#             */
/*   Updated: 2024/12/22 22:37:32 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	clean_node(t_node *node)
{
	t_node	*temp;

	while (node)
	{
		temp = node;
		node = node->next;
		free(temp);
	}
}

void	clean_graphics(t_game *game)
{
	if (!game)
		return ;
	free_graphic(game->mlx, game->wall_img);
	free_graphic(game->mlx, game->player_img);
	free_graphic(game->mlx, game->exit_img);
	free_graphic(game->mlx, game->collectible_img);
	free_graphic(game->mlx, game->empty_img);
}

void	clean_queue(t_queue *queue)
{
	if (queue)
	{
		free(queue->x);
		free(queue->y);
	}
}

void	clean_game(t_game *game)
{
	if (!game)
		return ;
	clean_graphics(game);
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	clean_map(game->map);
	free(game);
	game = NULL;
}

void	clean_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}
