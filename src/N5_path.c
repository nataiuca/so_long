/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A5_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:30:10 by natferna          #+#    #+#             */
/*   Updated: 2024/12/18 19:30:10 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int start_path(t_game *game, t_queue **queue, int ***visited)
{

	*queue = create_queue(game->width * game->height);
	if (!*visited || !*queue)
		return (0);
	enqueue(*queue, game->player_x, game->player_y);
	(*visited)[game->player_y][game->player_x] = 1;
	return (1);
}
void	enqueue(t_queue *queue, int x, int y)
{
	if (queue->rear == queue->capacity - 1)
		return ;
	if (queue->front == -1)
		queue->front = 0;
	queue->rear++;
	queue->x[queue->rear] = x;
	queue->y[queue->rear] = y;
}
void	dequeue(t_queue *queue, int *x, int *y)
{
	if (!steps_remaining(queue))
		return ;
	*x = queue->x[queue->front];
	*y = queue->y[queue->front];
	if (queue->front == queue->rear)
	{
		queue->front = -1;
		queue->rear = -1;
	}
	else
		queue->front++;
}
void find_path(t_game *game, t_queue *queue, int **visited,t_node *pos)
{
	pos->dir = 0;
	while (pos->dir < 4)
	{
		head_direction(game, queue, visited, pos);
		pos->dir++;
	}
}
void head_direction(t_game *game, t_queue *queue, int **visited,
		t_node *pos)
{
	int	nx;
	int	ny;
	int	dir_x[4]={-1,0,1,0};
	int	dir_y[4]={0,1,0,-1};
    
	nx = pos->x + dir_x[pos->dir];
	ny = pos->y + dir_y[pos->dir];
	if (is_valid_move(game, nx, ny, visited))
	{
		visited[ny][nx] = 1;
		enqueue(queue, nx, ny);
	}
}