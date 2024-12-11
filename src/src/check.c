/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:21:36 by natferna          #+#    #+#             */
/*   Updated: 2024/12/10 23:25:24 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_exit_reachable_after_collectibles(t_game *game)
{
	mark_exit_as_wall(game->map, game);
	ft_printf("Initialized player: x = %d, y = %d\n", game->player_x,
		game->player_y);
	ft_printf("Total collectibles: %d\n", game->collectibles);
	return (bfs(game));
}

void	check_exit_accessibility(t_game *game)
{
	if (!is_exit_reachable_after_collectibles(game))
	{
		ft_printf("Error: Exit is not accesible after collecting \
			all collectibles.\n");
		exit(1);
	}
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

int	check_map_dimensions(char **map, int *width)
{
	int	i;
	int	len;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (*width == -1)
			*width = len;
		else if (len != *width)
		{
			ft_printf("Error: Row %d is not the same \
			 length as the first row.\n", i);
			return (0);
		}
		if (!check_row(map[i], *width))
		{
			ft_printf("Error: Invalid row at index %d.\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}
