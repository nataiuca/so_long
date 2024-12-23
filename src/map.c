/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:52:13 by natferna          #+#    #+#             */
/*   Updated: 2024/12/23 18:26:02 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdlib.h>
#include <string.h>

void	get_map_size(char **map, int *height, int *width)
{
	*height = 0;
	*width = ft_strlen(map[0]);
	while (map[*height])
		(*height)++;
}

int	is_valid_map(char **map)
{
	if (!map || !map[0])
		return (ft_printf("Error: is_valid_map - Map is empty or NULL.\n"), 0);
	if (!valid_map_dimensions(map))
		return (ft_printf("Error: is_valid_map - Invalid map dimensions.\n"),
			0);
	if (!valid_map_borders(map))
		return (ft_printf("Error: is_valid_map - Invalid map frame.\n"), 0);
	if (!valid_map_elements(map))
		return (ft_printf("Error: is_valid_map - Missing \
		required elements"), 0);
	return (1);
}

int	valid_map_elements(char **map)
{
	int	i;
	int	j;
	int	map_items[3];
	int	tile_type;

	i = 0;
	ft_memset(map_items, 0, sizeof(map_items));
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			tile_type = valid_tile(map[i][j]);
			if (tile_type == 0)
				return (ft_printf("Error: valid_map_elements"), 0);
			else if (tile_type < 4)
				map_items[tile_type - 1]++;
			j++;
		}
		i++;
	}
	return (map_items[0] == 1 && map_items[1] == 1 && map_items[2] >= 1);
}

int	valid_map_dimensions(char **map)
{
	int	i;
	int	width;
	int	len;

	width = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len != width)
			return (ft_printf("Error: valid_map_dimensions"), 0);
		i++;
	}
	if (i == width)
		return (ft_printf("Error: valid_map_dimensions - Square map.\n"), 0);
	return (1);
}

int	valid_map_borders(char **map)
{
	int	height;
	int	width;
	int	i;
	int	j;

	get_map_size(map, &height, &width);
	i = 0;
	while (map[i])
	{
		if (i == 0 || i == height)
		{
			j = 0;
			while (map[i][j])
			{
				if (map[i][j] != '1')
					return (ft_printf("Error: valid_map_borders"), 0);
				j++;
			}
		}
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (ft_printf("Error: valid_map_borders"), 0);
		i++;
	}
	return (1);
}
