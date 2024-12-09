/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:02:11 by natferna          #+#    #+#             */
/*   Updated: 2024/12/09 15:01:07 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define BUFFER_SIZE 1024

# include <fcntl.h>
# include <mlx.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 64

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	void	*wall_img;
	void	*player_img;
	void	*exit_img;
	void	*collectible_img;
	void	*empty_img;
	int		img_width;
	int		img_height;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		move_count;
}			t_game;

int			process_map(char *file, t_game *game);
int			init_window(t_game *game);
void		render_map(t_game *game);
void		handle_events(t_game *game);
char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strndup(const char *s, size_t n);
int			ft_handle_format(const char *format, va_list args, int *i);
int			ft_printf(const char *format, ...);
int			ft_handle_char(char c);
int			ft_handle_str(char *str);
int			ft_handle_ptr(void *ptr);
int			ft_handle_int(int n);
int			ft_handle_unsigned(unsigned int n);
int			ft_handle_hex(unsigned int n, char format);
int			ft_put_hex(unsigned int n, char *base);
int			ft_put_hex_ptr(uintptr_t num);
int			ft_putnbr(long nb);
int			check_row(char *row, int row_index, int width);
int			check_map_elements(char **map);
int			check_row_borders(char *row);
int			check_valid_elements(char *row);
void		move_player(t_game *game, int x, int y);
char		*append_content(char *content, char *buffer, size_t *size,
				ssize_t bytes_read);
char		**ft_split(char const *s, char c);
int			validate_map(char **map);
void		free_split(char **split);
void		exit_game(t_game *game);
void		free_map(char **map);
void		initialize_player_and_collectibles(t_game *game);
void		explore_map(t_game *game, int x, int y, int **visited);
int			validate_accessibility(t_game *game);
void		init_visited(int **visited, t_game *game);
int			check_collectibles_and_exit(int **visited, t_game *game);
int			check_map_row_elements(char **map);
int			validate_map_format(t_game *game);
void		check_exit_accessibility(t_game *game);

#endif
