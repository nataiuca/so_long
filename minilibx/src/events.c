/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:07:29 by natferna          #+#    #+#             */
/*   Updated: 2024/12/09 15:05:00 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void move_player(t_game *game, int dx, int dy)
{
    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;

    // Verifica si la nueva posición está dentro de los límites del mapa
    if (new_x < 0 || new_x >= game->width || new_y < 0 || new_y >= game->height)
        return; // Evita mover fuera del mapa

    // Verifica si la nueva posición es una pared
    if (game->map[new_y][new_x] == '1')
        return; // No permite mover sobre paredes

    // Si es un coleccionable, recógelo
    if (game->map[new_y][new_x] == 'C')
    {
        game->collectibles--;
        game->map[new_y][new_x] = '0'; // Borra el coleccionable del mapa
    }

    // Si es la salida y ya no hay coleccionables, gana el juego
    if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
    {
		game->move_count++;
        ft_printf("¡Felicidades! Has ganado el juego en %d movimientos.\n", game->move_count);
        exit_game(game); // Limpia recursos y cierra el juego
        return;
    }

    // Mueve al jugador
    game->map[game->player_y][game->player_x] = '0'; // Limpia la posición anterior
    game->map[new_y][new_x] = 'P'; // Nueva posición del jugador
    game->player_x = new_x;
    game->player_y = new_y;

    // Incrementa el contador de movimientos y muestra el mensaje
    game->move_count++;
    ft_printf("Movimientos: %d\n", game->move_count);

    // Redibuja el mapa
    render_map(game);
}

int handle_key(int keycode, t_game *game)
{
    if (keycode == 65307)  // Esc para cerrar el juego
        exit(0);

    if (keycode == 'w')  // Tecla arriba (arriba en el mapa es -1 en y)
        move_player(game, 0, -1);
    if (keycode == 's')  // Tecla abajo (abajo en el mapa es +1 en y)
        move_player(game, 0, 1);
    if (keycode == 'a')  // Tecla izquierda (izquierda en el mapa es -1 en x)
        move_player(game, -1, 0);
    if (keycode == 'd')  // Tecla derecha (derecha en el mapa es +1 en x)
        move_player(game, 1, 0);

    return (0);
}

void	handle_events(t_game *game)
{
	mlx_key_hook(game->win, handle_key, game); // Maneja eventos de teclado
	mlx_loop(game->mlx); // Inicia el loop principal
}

void exit_game(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    free_map(game->map); // Libera el mapa si tienes una función de este tipo
    exit(0);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]); // Libera cada fila del mapa
		i++;
	}
	free(map); // Libera el array de punteros
}
