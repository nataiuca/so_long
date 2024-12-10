/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:37:49 by natferna          #+#    #+#             */
/*   Updated: 2024/12/10 23:34:10 by natferna         ###   ########.fr       */
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
	if (!check_map_dimensions(map, &width))
		return (0);
	if (!check_map_elements(map))
	{
		ft_printf("Error: Missing required elements (P, E, C).\n");
		return (0);
	}
	return (1);
}

void	update_element_count(char tile, int *player, int *exit,
		int *collectible)
{
	if (tile == 'P')
	{
		(*player)++;
	}
	else if (tile == 'E')
	{
		(*exit)++;
	}
	else if (tile == 'C')
	{
		(*collectible)++;
	}
}

void	print_element_position(char tile, int i, int j)
{
	ft_printf("call print_element_position\n");
	if (tile == 'P')
		ft_printf("Player found at (%d, %d)\n", i, j);
	else if (tile == 'E')
		ft_printf("Exit found at (%d, %d)\n", i, j);
	else if (tile == 'C')
		ft_printf("Collectible found at (%d, %d)\n", i, j);
}

int	validate_elements_count(int player, int exit, int collectible)
{
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
	return (validate_elements_count(player_found, exit_found,
			collectible_found));
}
