/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 21:10:24 by natferna          #+#    #+#             */
/*   Updated: 2024/12/09 14:53:39 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	validate_map_format(t_game *game)
{
	int	i;
	int	width;

	i = 0;
	width = -1;
	if (game == NULL)
	{
		ft_printf("Error: El puntero 'game' es NULL.\n");
		return (0);
	}
	if (game->map == NULL)
	{
		ft_printf("Error: El mapa no está inicializado correctamente.\n");
		return (0);
	}
	while (game->map[i])
	{
		if (width == -1)
			width = ft_strlen(game->map[i]);
		else if ((int)ft_strlen(game->map[i]) != width)
		{
			ft_printf("Error: Row \
				%d is not the same length as the first row.\n", i);
			return (0);
		}
		if (!check_row(game->map[i], i, width))
		{
			ft_printf("Error: Invalid row at index %d.\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

