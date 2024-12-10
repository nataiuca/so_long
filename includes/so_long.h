/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:02:11 by natferna          #+#    #+#             */
/*   Updated: 2024/12/10 23:38:22 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define BUFFER_SIZE 1024

# include <fcntl.h>
# include <mlx.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 64

typedef struct s_node
{
	int				x;
	int				y;
	int				dir;
	struct s_node	*next;
}					t_node;

typedef struct s_queue
{
	int				*x;
	int				*y;
	int				front;
	int				rear;
	int				capacity;
}					t_queue;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	char			**map;
	void			*wall_img;
	void			*player_img;
	void			*exit_img;
	void			*collectible_img;
	void			*empty_img;
	int				exit_found;
	int				collected;
	int				img_width;
	int				img_height;
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	int				collectibles;
	int				move_count;
}					t_game;

int					process_map(char *file, t_game *game);
int					init_window(t_game *game);
void				render_map(t_game *game);
void				handle_events(t_game *game);
char				*get_next_line(int fd);
size_t				ft_strlen(const char *s);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strdup(const char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strndup(const char *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
int					ft_handle_format(const char *format, va_list args, int *i);
int					ft_printf(const char *format, ...);
int					ft_handle_char(char c);
int					ft_handle_str(char *str);
int					ft_handle_ptr(void *ptr);
int					ft_handle_int(int n);
int					ft_handle_unsigned(unsigned int n);
int					ft_handle_hex(unsigned int n, char format);
int					ft_put_hex(unsigned int n, char *base);
int					ft_put_hex_ptr(uintptr_t num);
int					ft_putnbr(long nb);
char				**ft_split(char const *s, char c);
int					**init_visited(int width, int height);
void				free_visited(int **visited, int height);
int					validate_accessibility(t_game *game);
void				free_map(char **map);
void				find_exit_position(char **map, t_game *game, int *exit_x,
						int *exit_y);
int					**allocate_visited(int width, int height);
int					is_exit_found(t_game *game, int x, int y);
void				check_neighbors(t_game *game, t_queue *queue, int **visited,
						t_node *pos);
int					bfs(t_game *game);
int					is_exit_reachable_after_collectibles(t_game *game);
void				check_exit_accessibility(t_game *game);
int					check_row_borders(char *row);
int					check_valid_elements(char *row);
int					check_map_dimensions(char **map, int *width);
int					handle_exit(t_game *game, int x, int y);
void				move_player(t_game *game, int dx, int dy);
int					handle_key(int keycode, t_game *game);
void				free_map_rows(int **visited, int height);
void				free_resources(int **visited, t_queue *queue, int height);
int					is_valid_move(t_game *game, int x, int y, int **visited);
void				handle_collectible(t_game *game, int x, int y);
int					handle_exit(t_game *game, int x, int y);
void				find_exit_position(char **map, t_game *game, int *exit_x,
						int *exit_y);
void				mark_exit_as_wall(char **map, t_game *game);
char				*append_content(char *content, char *buffer, size_t *size,
						ssize_t bytes);
int					process_map(char *map_file, t_game *game);
t_queue				*create_queue(int capacity);
bool				is_queue_empty(t_queue *queue);
void				enqueue(t_queue *queue, int x, int y);
void				dequeue(t_queue *queue, int *x, int *y);
void				free_queue(t_queue *queue);
void				render_tile(t_game *game, int x, int y);
void				render_row(t_game *game, int y);
void				render_map(t_game *game);
int					validate_map(char **map);
void				update_element_count(char tile, int *player, int *exit,
						int *collectible);
int					validate_elements_count(int player, int exit,
						int collectible);
int					check_map_elements(char **map);
int					load_image(t_game *game, char *file, void **img);
int					print_image_loaded(char *image_name);
int					init_window(t_game *game);
void				handle_events(t_game *game);
void				exit_game(t_game *game);
int					check_row(char *row, int width);
void				initialize_player_and_collectibles(t_game *game);
void				process_tile(t_game *game, int x, int y);
void				check_exit_collision(t_game *game, int x, int y);
void				free_split(char **split_array);
int					check_elements(char element, int *player_found,
						int *exit_found, int *collectible_found);
void				init_visited_player(t_game *game, int ***visited);
void				free_visited_player(t_game *game, int **visited);
void				init_directions(int dir_x[4], int dir_y[4]);
void				check_direction(t_game *game, t_queue *queue, int **visited,
						t_node *pos);

#endif
