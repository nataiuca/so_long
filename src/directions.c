/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:57:41 by natferna          #+#    #+#             */
/*   Updated: 2024/12/11 17:03:34 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_directions(int dir_x[4], int dir_y[4])
{
	dir_x[0] = -1;
	dir_x[1] = 1;
	dir_x[2] = 0;
	dir_x[3] = 0;
	dir_y[0] = 0;
	dir_y[1] = 0;
	dir_y[2] = -1;
	dir_y[3] = 1;
}

void	check_direction(t_game *game, t_queue *queue, int **visited,
		t_node *pos)
{
	int	nx;
	int	ny;
	int	dir_x[4];
	int	dir_y[4];

	init_directions(dir_x, dir_y);
	nx = pos->x + dir_x[pos->dir];
	ny = pos->y + dir_y[pos->dir];
	if (is_valid_move(game, nx, ny, visited))
	{
		visited[ny][nx] = 1;
		enqueue(queue, nx, ny);
	}
}

void	check_neighbors(t_game *game, t_queue *queue, int **visited,
		t_node *pos)
{
	pos->dir = 0;
	while (pos->dir < 4)
	{
		check_direction(game, queue, visited, pos);
		pos->dir++;
	}
}

void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	check_exit_positions(int i, int j, int width, int height)
{
	if ((i == 0 && (j == 0 || j == width - 1)) || (i == height - 1 && (j == 0
				|| j == width - 1)))
		return (0);
	return (1);
}
