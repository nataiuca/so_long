/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:35:53 by natferna          #+#    #+#             */
/*   Updated: 2024/12/28 00:22:47 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	load_map(char *map_file, t_game *game)
{
	char	*map_content;

	map_content = read_file(map_file);
	if (!map_content)
	{
		free(map_content);
		map_content = NULL;
		return (ft_printf("Error: Load_map -Map file could not be loaded.\n"),
			0);
	}
	game->map = ft_split(map_content, '\n');
	free(map_content);
	if (!game->map || !game->map[0])
	{
		return (ft_printf("Error: Load_map - Empty map.\n"), 0);
	}
	get_map_size(game->map, &game->height, &game->width);
	if (!is_valid_map(game->map))
		return (ft_printf("Error: Load_map - Invalid map.\n"), 0);
	return (load_elements(game), 1);
}

void	load_elements(t_game *game)
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
			load_tile(game, x, y);
			x++;
		}
		y++;
	}
	game->move_count = 0;
}

void	load_tile(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'P')
	{
		game->player_x = x;
		game->player_y = y;
	}
	else if (game->map[y][x] == 'C')
		game->collectibles++;
}

int	load_image(t_game *game, char *file, void **img)
{
	*img = mlx_xpm_file_to_image(game->mlx, file, &game->img_width,
			&game->img_height);
	return (*img != NULL);
}

void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
