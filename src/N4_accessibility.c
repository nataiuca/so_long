/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A4_accessibility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:11:14 by natferna          #+#    #+#             */
/*   Updated: 2024/12/18 19:11:14 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_accessible(t_game *game)
{
	t_queue	*queue;
	int		**visited;
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (ft_printf("Error: is_accessible -\
		 Unable to allocate node memory.\n"),0);
	visited = init_visited(game->width, game->height);
	if (!visited)
		return (ft_printf("Error: is_accessible -\
		 Unable to initialize visited.\n"),0);
	if (!start_path(game, &queue, &visited))
		return (0);
	while (steps_remaining(queue))
	{
		node=peek(queue);
		dequeue(queue, &node->x, &node->y);
		process_node(game, queue, visited, node);
	}
	clean_node(node);
	clean_queue(queue);
	clean_visited(visited);
	return (game->collected == game->collectibles && game->exit_found);
}
int	**init_visited(int width, int height)
{
	int	**visited;
	int	i;
	int	j;

	visited = (int **)malloc(sizeof(int *) * height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = (int *)malloc(sizeof(int) * width);
		if (!visited[i])
			return (NULL);
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
		find_path(game, queue, visited, node);
}
int	is_valid_move(t_game *game, int x, int y, int **visited)
{
	return (x >= 0 && x < game->width && y >= 0 && y < game->height
		&& !visited[y][x] && game->map[y][x] != '1');
}
bool steps_remaining(t_queue *queue)
{
	return (queue->front != -1);
}