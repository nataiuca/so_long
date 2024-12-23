/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 22:30:23 by natferna          #+#    #+#             */
/*   Updated: 2024/12/23 22:31:24 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_graphic(void *mlx, void *img)
{
	if (img)
	{
		mlx_destroy_image(mlx, img);
		img = NULL;
	}
}

void clean_visited(int **visited, int height)
{
    int i = 0;

    if (visited == NULL)
        return;

    while (i < height)
    {
        free(visited[i]);
		visited[i] = NULL;
        i++;
    }
    free(visited);
	visited = NULL;
}

void destroy_queue(t_queue *queue)
{
    if (!queue)
        return;
    if (queue->x)
	{
        free(queue->x);
		queue->x = NULL;
	}
    if (queue->y)
	{
        free(queue->y);
		queue->y = NULL;
	}
    free(queue);
	queue = NULL;
}
