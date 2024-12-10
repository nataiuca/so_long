/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:08:57 by natferna          #+#    #+#             */
/*   Updated: 2024/12/10 23:22:33 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	**allocate_visited(int width, int height)
{
	int	**visited;
	int	i;
	int	j;

	visited = (int **)malloc(sizeof(int *) * height);
	i = 0;
	while (i < height)
	{
		visited[i] = (int *)malloc(sizeof(int) * width);
		j = 0;
		while (j < width)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
	return (visited);
}

int	is_exit_found(t_game *game, int x, int y)
{
	return (game->map[y][x] == 'E');
}

int	initialize_bfs(t_game *game, t_queue **queue, int ***visited)
{
	*visited = allocate_visited(game->width, game->height);
	*queue = create_queue(game->width * game->height);
	if (!*visited || !*queue)
		return (0);
	enqueue(*queue, game->player_x, game->player_y);
	(*visited)[game->player_y][game->player_x] = 1;
	return (1);
}

void	process_node(t_game *game, t_queue *queue, int **visited, t_node *node)
{
	handle_collectible(game, node->x, node->y);
	if (handle_exit(game, node->x, node->y))
		return ;
	if (is_exit_found(game, node->x, node->y))
	{
		game->exit_found = 1;
		return ;
	}
	else
		check_neighbors(game, queue, visited, node);
}

int	bfs(t_game *game)
{
	t_queue	*queue;
	int		**visited;
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		printf("[ERROR] Memory allocation failed for queue.\n");
		return (0);
	}
	if (!initialize_bfs(game, &queue, &visited))
		return (0);
	while (!is_queue_empty(queue))
	{
		dequeue(queue, &node->x, &node->y);
		process_node(game, queue, visited, node);
	}
	free_visited(visited, game->height);
	free_queue(queue);
	return (game->collected == game->collectibles && game->exit_found);
}
