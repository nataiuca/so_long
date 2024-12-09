/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:37:49 by natferna          #+#    #+#             */
/*   Updated: 2024/12/09 15:00:43 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdlib.h>

int	validate_map(char **map)
{
	int	i;
	int	width;	

	i = 0;
	width = -1;
	if (!map || !map[0])
	{
		ft_printf("Error: Map is empty or NULL.\n");
		return (0);
	}
	while (map[i])
	{
		if (width == -1)
			width = ft_strlen(map[i]);
		else if ((int)ft_strlen(map[i]) != width)
		{
			ft_printf("Error: Row %d is not the same length as the first row.\n", i);
			return (0);
		}
		if (!check_row(map[i], i, width))
		{
			ft_printf("Error: Invalid row at index %d.\n", i);
			return (0);
		}
		i++;
	}
	if (!check_map_elements(map))
	{
		ft_printf("Error: Missing required elements (P, E, C).\n");
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
			if (map[i][j] == 'P')
			{
				player_found++;
				ft_printf("Player found at (%d, %d)\n", i, j);
			}
			else if (map[i][j] == 'E')
			{
				exit_found++;
				ft_printf("Exit found at (%d, %d)\n", i, j);
			}
			else if (map[i][j] == 'C')
			{
				collectible_found++;
				ft_printf("Collectible found at (%d, %d)\n", i, j);
			}
			j++;
		}
		i++;
	}
	if (player_found != 1 || exit_found != 1 || collectible_found <1)
	{
		ft_printf("Error: Missing P, E or C on the map.\n");
		return (0);
	}
	return (1);
}

int	check_row(char *row, int i, int width)
{
	if (i == 0 || row[i + 1] == '\0')
		return (check_row_borders(row));
	if (row[0] != '1' || row[width - 1] != '1')
	{
		ft_printf("Error: Invalid border in row %d\n", i);
		return (0);
	}
	return (check_valid_elements(row));
}

int	check_row_borders(char *row)
{
	int	j;

	j = 0;
	while (row[j] != '\0')
	{
		if (row[j] != '1')
		{
			ft_printf("Error: Invalid character at the border (not '1').\n");
			return (0);
		}
		j++;
	}
	return (1);
}

int	check_valid_elements(char *row)
{
	int	j;

	j = 0;
	while (row[j] != '\0')
	{
		if (row[j] != '1' && row[j] != '0' && row[j] != 'P' && row[j] != 'E'
			&& row[j] != 'C')
		{
			ft_printf("Error: Invalid character '%c' found.\n", row[j]);
			return (0);
		}
		j++;
	}
	return (1);
}
