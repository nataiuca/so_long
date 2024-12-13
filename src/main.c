/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:08:03 by natferna          #+#    #+#             */
/*   Updated: 2024/12/13 16:41:19 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Usage: ./so_long <map_file>\n");
		return (1);
	}
	if (!process_map(argv[1], &game))
	{
		return (ft_printf("Error: Invalid map\n"), 1);
	}
	if (!validate_accessibility(&game))
	{
		ft_printf("Error: No path to exit or collectibles unreachable\n");
		return (1);
	}
	if (!init_window(&game))
	{
		return (ft_printf("Error: Could not initialize window\n"), 1);
	}
	render_map(&game);
	game.collected = 0;
	handle_events(&game);
	return (0);
}