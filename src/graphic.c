/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 22:30:23 by natferna          #+#    #+#             */
/*   Updated: 2024/12/22 23:08:52 by natferna         ###   ########.fr       */
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

void	clean_visited(int **visited, int height)
{
	int	i;

	if (visited == NULL)
		return ;
	i = 0;
	while (i < height && visited[i] != NULL)
	{
		free(visited[i]);
		visited[i] = NULL;
		i++;
	}
	free(visited);
}
