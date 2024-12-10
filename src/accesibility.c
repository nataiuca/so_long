/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accesibility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:47:54 by natferna          #+#    #+#             */
/*   Updated: 2024/12/10 17:45:24 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

int	validate_accessibility(t_game *game)
{
	int	**visited;
	int	result;

	visited = init_visited(game->width, game->height);
	if (!visited)
		return (0);
	result = bfs(game);
	free_visited(visited, game->height);
	return (result);
}

void	free_map(char **map)
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
}

void	initialize_player_and_collectibles(t_game *game)
{
	int	y;
	int	x;

	game->collectibles = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			process_tile(game, x, y);
			x++;
		}
		y++;
	}
	ft_printf("Coleccionables totales: %d\n", game->collectibles);
}

int	check_elements(char element, int *player_found, int *exit_found,
		int *collectible_found)
{
	if (element == 'P')
		(*player_found)++;
	else if (element == 'E')
		(*exit_found)++;
	else if (element == 'C')
		(*collectible_found)++;
	return (1);
}
