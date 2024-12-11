/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:34:14 by natferna          #+#    #+#             */
/*   Updated: 2024/12/10 21:10:38 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_map_rows(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
}

void	free_resources(int **visited, t_queue *queue, int height)
{
	free_map_rows(visited, height);
	free(visited);
	free_queue(queue);
}

int	check_row(char *row, int width)
{
	int	j;

	j = 0;
	while (row[j])
	{
		if (row[j] != '1' && row[j] != '0' && row[j] != 'P' && row[j] != 'E'
			&& row[j] != 'C')
		{
			return (0);
		}
		j++;
	}
	if (j != width)
	{
		return (0);
	}
	return (1);
}

void	free_visited_player(t_game *game, int **visited)
{
	int	i;

	i = 0;
	while (i < game->height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

void	init_visited_player(t_game *game, int ***visited)
{
	int	i;

	*visited = malloc(game->height * sizeof(int *));
	if (!*visited)
		return ;
	i = 0;
	while (i < game->height)
	{
		(*visited)[i] = malloc(game->width * sizeof(int));
		ft_memset((*visited)[i], 0, game->width * sizeof(int));
		i++;
	}
}
