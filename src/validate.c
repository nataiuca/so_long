/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:37:49 by natferna          #+#    #+#             */
/*   Updated: 2024/12/11 14:30:55 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdlib.h>

int	validate_map(char **map)
{
	int	width;

	width = -1;
	if (!map || !map[0])
	{
		ft_printf("Error: Map is empty or NULL.\n");
		return (0);
	}
	ft_printf("Debug: Map is valid and not empty.\n");
	if (!check_map_dimensions(map, &width))
	{
		ft_printf("Error: Invalid map dimensions.\n");
		return (0);
	}
	ft_printf("Debug: Map dimensions are valid.\n");
	if (!check_map_elements(map))
	{
		ft_printf("Error: Missing required elements (P, E, C).\n");
		return (0);
	}
	ft_printf("Debug: Map elements (P, E, C) are correctly placed.\n");
	return (1);
}

void	update_element_count(char tile, int *player, int *exit,
		int *collectible)
{
	if (tile == 'P')
	{
		(*player)++;
		ft_printf("Debug: Player found, total players: %d.\n", *player);
	}
	else if (tile == 'E')
	{
		(*exit)++;
		ft_printf("Debug: Exit found, total exits: %d.\n", *exit);
	}
	else if (tile == 'C')
	{
		(*collectible)++;
		ft_printf("Debug: Collectible found, total collectibles: %d.\n",
			*collectible);
	}
}

int	validate_elements_count(int player, int exit, int collectible, char **map)
{
	int	i;
	int	j;
	int	height;
	int	width;

	i = 0;
	get_map_dimensions(map, &height, &width);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				if (!check_exit_positions(i, j, width, height))
					return (0);
			j++;
		}
		i++;
	}
	if (player != 1 || exit != 1 || collectible < 1)
	{
		ft_printf("Error: Missing P, E or C on the map.\n");
		return (0);
	}
	return (1);
}

int	check_map_elements(char **map)
{
	int	i;
	int	j;
	int	player_found;
	int	exit_found;
	int	collectible_found;

	i = 0;
	player_found = 0;
	exit_found = 0;
	collectible_found = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			check_elements(map[i][j], &player_found, &exit_found,
				&collectible_found);
			j++;
		}
		i++;
		if (player_found == 1 && exit_found == 1 && collectible_found >= 1)
			break ;
	}
	return (validate_elements_count(player_found, exit_found, collectible_found,
			map));
}
