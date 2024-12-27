/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:04:43 by natferna          #+#    #+#             */
/*   Updated: 2024/12/28 00:21:25 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	clean_node(t_node *node)
{

	if (node)
	{
		node->next = NULL;
		node->x = 0;
		node->y = 0;
		free(node);
	}
	node = NULL;
}

void	clean_graphics(t_game *game)
{
	if (!game)
		return ;
	if (game->wall_img)
		free_graphic(game->mlx, game->wall_img);
	if (game->player_img)
		free_graphic(game->mlx, game->player_img);
	if (game->exit_img)
		free_graphic(game->mlx, game->exit_img);
	if (game->collectible_img)
		free_graphic(game->mlx, game->collectible_img);
	if (game->empty_img)
		free_graphic(game->mlx, game->empty_img);
}

void	clean_queue(t_queue *queue)
{
	if (queue)
	{
		free(queue->x);
		free(queue->y);
	}
	free(queue);
	queue = NULL;
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
	if (game->map)
		clean_map(game->map);
		game->map = NULL;
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
		map[i] = NULL;
		i++;
	}
	free(map);
}
