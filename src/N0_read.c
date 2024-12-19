/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A0_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:29:18 by natferna          #+#    #+#             */
/*   Updated: 2024/12/18 21:29:18 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*read_loop(int fd, char *content, size_t *total_size){
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
void	clean_visited(int **visited)
{
	int	i;
	i = 0;
	while (visited[i])
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}
