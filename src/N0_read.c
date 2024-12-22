/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N0_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:29:18 by natferna          #+#    #+#             */
/*   Updated: 2024/12/22 21:53:15 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*read_loop(int fd, char *content, size_t *total_size)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (safe_free((void**)&content), NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		content = append_content(content, buffer, total_size, bytes_read);
		if (!content)
			return (free(buffer), NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read < 0)
		return (safe_free((void**)&content), NULL);
	return (content);
}

char	*read_file(const char *filename)
{
	int		fd;
	char	*content;
	size_t	total_size;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = malloc(1);
	if (!content)
		return (NULL);
	content[0] = '\0';
	total_size = 0;
	content = read_loop(fd, content, &total_size);
	close(fd);
	return (content);
}

char	*append_content(char *content, char *buffer, size_t *size,
		ssize_t bytes)
{
	char	*new_content;
	size_t	new_size;
	size_t	i;

	new_size = *size + bytes;
	new_content = malloc(new_size + 1);
	if (!new_content)
		return (safe_free((void**)&content), NULL);
	i = 0;
	while (i < *size)
	{
		new_content[i] = content[i];
		i++;
	}
	free(content);
	while (i < new_size)
	{
		new_content[i] = buffer[i - *size];
		i++;
	}
	new_content[new_size] = '\0';
	*size = new_size;
	return (new_content);
}

void clean_visited(int **visited, int height)
{
    if (visited == NULL)  // Si el puntero a la matriz es NULL, no hacemos nada
        return;

    int i = 0;
    while (i < height && visited[i] != NULL)  // Mientras haya filas por liberar y dentro del tamaño válido
    {
        ft_printf("limpiando fila %d\n", i);
        free(visited[i]);  // Liberamos la memoria de la fila actual
        visited[i] = NULL;  // Asignamos NULL para evitar accesos accidentales
        i++;  // Avanzamos a la siguiente fila
    }

    ft_printf("limpiando visited\n");
    free(visited);  // Finalmente, liberamos el puntero principal de la matriz
    // No es necesario hacer visited = NULL aquí, ya que esto no afecta al puntero original.
}
