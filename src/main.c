/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:20:23 by natferna          #+#    #+#             */
/*   Updated: 2024/12/19 20:58:52 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (argc != 2)
		return (ft_printf("Usage: ./so_long <map_file>\n"), 1);
	if (!load_map(argv[1], game))
		return (close_game(game, "Error: Unable to load map."), 1);
	// WIP
	ft_printf ("mapa ok!");
	if (!is_accessible(game))
		return (close_game(game,
				"Error: No path to exit or collectibles unreachable."), 1);
	ft_printf("camino ok");
	if (!init_window(game))
		return (close_game(game, "Error: Could not initialize window."), 1);
	ft_printf("iniciando ventana");
	render_map(game);
	game->collected = 0;
	handle_events(game);
	return (0);
}
