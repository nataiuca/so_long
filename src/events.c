/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:07:29 by natferna          #+#    #+#             */
/*   Updated: 2024/12/13 16:40:35 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	handle_exit(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'E' && game->collected == game->collectibles)
	{
		game->move_count++;
		ft_printf("Congrats! You won the game in %d moves.\n",
			game->move_count);
		exit_game(game);
		return (1);
	}
	return (0);
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;
	int	**visited;

	init_visited_player(game, &visited);
	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (!is_valid_move(game, new_x, new_y, visited))
		return ;
	free(visited);
	handle_collectible(game, new_x, new_y);
	if (handle_exit(game, new_x, new_y))
		return ;
	if (!is_exit_found(game, new_x, new_y))
	{
		game->map[game->player_y][game->player_x] = '0';
		game->map[new_y][new_x] = 'P';
		game->player_x = new_x;
		game->player_y = new_y;
		game->move_count++;
		ft_printf("Moves: %d\n", game->move_count);
		render_map(game);
	}
	return ;
}

int	handle_key(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 'w')
		move_player(game, 0, -1);
	if (keycode == 's')
		move_player(game, 0, 1);
	if (keycode == 'a')
		move_player(game, -1, 0);
	if (keycode == 'd')
		move_player(game, 1, 0);
	return (0);
}

void	process_tile(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'P')
	{
		game->player_x = x;
		game->player_y = y;
	}
	else if (game->map[y][x] == 'C')
		game->collectibles++;
	else if (game->map[y][x] == 'E')
	{
		check_exit_collision(game, x, y);
	}
}

void	check_exit_collision(t_game *game, int x, int y)
{
	if (game->player_x == x && game->player_y == y)
	{
		ft_printf("Error: Exit is in the same position \
			as the player.\n");
		exit(1);
	}
}
