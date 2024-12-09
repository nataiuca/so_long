/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accesibility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:47:54 by natferna          #+#    #+#             */
/*   Updated: 2024/12/09 19:33:55 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int validate_accessibility(t_game *game)
{
    int **visited;
    int i;
	
    // Inicializamos la matriz de visitados
    visited = (int **)malloc(sizeof(int *) * game->height);
    for (i = 0; i < game->height; i++)
    {
        visited[i] = (int *)malloc(sizeof(int) * game->width);
        for (int j = 0; j < game->width; j++)
            visited[i][j] = 0;
    }

    // Verificamos la accesibilidad usando BFS
    int result = bfs(game->player_x, game->player_y, game->map, game->width, game->height, game->collectibles);

    // Liberamos la memoria de visitados
    for (i = 0; i < game->height; i++)
        free(visited[i]);
    free(visited);

    return result;
}
