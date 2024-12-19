/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A6_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:55:48 by natferna          #+#    #+#             */
/*   Updated: 2024/12/18 19:55:48 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	handle_events(t_game *game)
{
	mlx_key_hook(game->win, handle_key, game);
	mlx_hook(game->win, 17, 0, exit_event, game);
	mlx_loop(game->mlx);
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
void handle_collectible(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'C')
		game->collected++;
}
int	handle_exit(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'E' && game->collected == game->collectibles)
	{
		game->move_count++;
		ft_printf("Congrats! You won the game in %d moves.\n",
			game->move_count);
		close_game(game,"Win!");
		return (1);
	}
	return (0);
}
int	exit_event(void *param)
{
	t_game	*game;
	game = (t_game *)param;
	return (close_game(game,"--- Exit event triggered ---"),0);
}
