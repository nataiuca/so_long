/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:14:17 by natferna          #+#    #+#             */
/*   Updated: 2024/12/10 23:29:14 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static char	*read_loop(int fd, char *content, size_t *total_size)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(content), NULL);
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
		return (free(content), NULL);
	return (content);
}

static char	*read_file(const char *filename)
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
		return (free(content), NULL);
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

int	process_map(char *map_file, t_game *game)
{
	char	*map_content;
	char	**map_lines;

	map_content = read_file(map_file);
	if (!map_content)
	{
		ft_printf("Error: Map file could not be loaded.\n");
		return (0);
	}
	map_lines = ft_split(map_content, '\n');
	free(map_content);
	if (!map_lines || !map_lines[0])
		return (free_split(map_lines), 0);
	game->map = map_lines;
	game->width = ft_strlen(map_lines[0]);
	game->height = 0;
	while (map_lines[game->height])
		game->height++;
	ft_printf("Map loaded: width = %d, height = %d\n", game->width,
		game->height);
	if (!validate_map(game->map))
		return (free_split(map_lines), 0);
	initialize_player_and_collectibles(game);
	game->move_count = 0;
	return (1);
}
