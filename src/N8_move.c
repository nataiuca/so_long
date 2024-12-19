/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A8_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:10:41 by natferna          #+#    #+#             */
/*   Updated: 2024/12/18 20:10:41 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;
	int	**visited;

	visited = init_visited(game->width,game->height);
	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (!is_valid_move(game, new_x, new_y, visited))
		return ;
	clean_visited(visited);

	handle_collectible(game, new_x, new_y);
	if (handle_exit(game, new_x, new_y))
		return ;
	if (!is_exit_found(game, new_x, new_y))
	{
		game->map[game->player_y][game->player_x] = '0';
		game->map[new_y][new_x] = 'P';
		game->player_x = new_x;
		game->player_y = new_y;
		game->move_count++;
		ft_printf("Moves: %d\n", game->move_count);
		render_map(game);
	}
	return ;
}

int	is_exit_found(t_game *game, int x, int y)
{
	return (game->map[y][x] == 'E');
}
int valid_tile(char tile)
{
    if (tile=='P')
        return 1;
    else if (tile=='E')
        return 2;
    else if (tile=='C')
        return 3;
    else if (tile=='0')
        return 4;
    else if (tile=='1')
        return 4;
    else return 0;
}
t_queue	*create_queue(int capacity)
{
	t_queue	*queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	queue->x = (int *)malloc(sizeof(int) * capacity);
	queue->y = (int *)malloc(sizeof(int) * capacity);
	queue->front = -1;
	queue->rear = -1;
	queue->capacity = capacity;
	return (queue);
}
t_node *peek(t_queue *queue) 
{
	t_node	*node;

	node = malloc(sizeof(t_node));
    if (node == NULL)
        return NULL;
    if (!queue->front) 
	{
        return NULL; // Retorna NULL si la cola está vacía
    }
	node->x = queue->x[queue->front];  // Asigna la coordenada x
    node->y = queue->y[queue->front];  // Asigna la coordenada y
    return node;
}

