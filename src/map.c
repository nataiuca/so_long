/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 21:10:24 by natferna          #+#    #+#             */
/*   Updated: 2024/12/09 20:48:14 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdio.h>
#include <stdlib.h>

int bfs(int start_x, int start_y, char **map, int width, int height, int total_collectibles)
{
    // Definir los desplazamientos en las 4 direcciones: izquierda, derecha, arriba, abajo
    int dir_x[] = { -1, 1, 0, 0 };  // Desplazamiento en el eje x (horizontal)
    int dir_y[] = { 0, 0, -1, 1 };  // Desplazamiento en el eje y (vertical)

    // Crear la matriz de visitados
    int **visited = (int **)malloc(sizeof(int *) * height);
    for (int i = 0; i < height; i++)
    {
        visited[i] = (int *)malloc(sizeof(int) * width);
        for (int j = 0; j < width; j++)
            visited[i][j] = 0;  // Inicializar con 0 (no visitado)
    }

    // Crear la cola para BFS con capacidad suficiente
    t_queue *queue = create_queue(width * height);
    enqueue(queue, start_x, start_y);
    visited[start_y][start_x] = 1;

    int collected = 0;  // Contador de coleccionables recogidos
    int exit_found = 0; // Indicador de si se ha encontrado la salida

    printf("Iniciando BFS desde la posición (%d, %d)\n", start_x, start_y);
    printf("Coleccionables totales: %d\n", total_collectibles);

    // Ejecutar BFS
    while (!is_queue_empty(queue))
    {
        int x, y;
        dequeue(queue, &x, &y);

        printf("Explorando: (%d, %d) - Contenido: %c\n", x, y, map[y][x]);

        // Si encontramos la salida, marcarlo
        if (map[y][x] == 'E') {
            exit_found = 1;
            printf("Salida encontrada en: (%d, %d)\n", x, y);
        }

        // Si encontramos un coleccionable, incrementamos el contador
        if (map[y][x] == 'C') {
            collected++;
            printf("Coleccionable recogido en: (%d, %d). Total recogidos: %d/%d\n", x, y, collected, total_collectibles);
        }

       if (map[y][x] != 'E')
	   {
	    	// Explorar las 4 direcciones
        	for (int dir = 0; dir < 4; dir++)
        	{
            	int nx = x + dir_x[dir];
            	int ny = y + dir_y[dir];

            	// Comprobar si la nueva posición es válida
            	if (nx >= 0 && nx < width && ny >= 0 && ny < height && !visited[ny][nx] && map[ny][nx] != '1')
            	{
                	visited[ny][nx] = 1;
                	enqueue(queue, nx, ny);
                	printf("Encolando: (%d, %d) - Contenido: %c\n", nx, ny, map[ny][nx]);
        
		    	}
			}		
        }
    }

    // Si hemos recogido todos los coleccionables y encontrado la salida, podemos finalizar
    if (collected == total_collectibles && exit_found) {
        printf("Todos los coleccionables recogidos y salida alcanzada. El mapa es accesible.\n");
        // Liberar memoria
        for (int i = 0; i < height; i++) {
            free(visited[i]);
        }
        free(visited);

        free_queue(queue);
        return 1;  // El mapa es accesible
    }

    // Si hemos recorrido todo el mapa y no hemos encontrado todos los coleccionables o la salida
    printf("No se encontró un camino válido o los coleccionables no fueron recogidos. El mapa no es accesible.\n");

    free_queue(queue);

    // Liberar memoria de visited
    for (int i = 0; i < height; i++) {
        free(visited[i]);
    }
    free(visited);

    return 0;  // El mapa no es accesible
}

// Función para liberar recursos
void free_resources(int **visited, t_queue *queue, int height) {
    for (int i = 0; i < height; i++) {
        free(visited[i]);
    }
    free(visited);
    free_queue(queue);
}

void mark_exit_as_wall(char **map, t_game *game) {
    int exit_x = game->player_x;
    int exit_y = game->player_y;

    // Encuentra la salida en el mapa (suponemos que hay solo una salida)
    for (int y = 0; y < game->height; y++) {
        for (int x = 0; x < game->width; x++) {
            if (map[y][x] == 'E') {
                exit_x = x;
                exit_y = y;
                break;
            }
        }
    }

    // Marca la salida como pared antes de recoger todos los coleccionables
    map[exit_y][exit_x] = '1';
}

int is_exit_reachable_after_collectibles(t_game *game) {
    // Marca la salida como una pared
    mark_exit_as_wall(game->map, game);

	ft_printf("Jugador inicializado en: x = %d, y = %d\n", game->player_x, game->player_y);
	ft_printf("Coleccionables totales: %d\n", game->collectibles);
    // Ejecuta BFS para ver si la salida es alcanzable después de recoger todos los coleccionables
    return bfs(game->player_x, game->player_y, game->map, game->width, game->height, game->collectibles);
}

void check_exit_accessibility(t_game *game) {
    if (!is_exit_reachable_after_collectibles(game)) {
        ft_printf("Error: La salida no es accesible después de recoger todos los coleccionables.\n");
        exit(1);  // Detener el juego si la salida no es accesible
    }
}
