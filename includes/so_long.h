/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:02:11 by natferna          #+#    #+#             */
/*   Updated: 2024/12/11 14:26:48 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define BUFFER_SIZE 1024

# include <fcntl.h>
# include <mlx.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
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
//A0_read
char	*read_loop(int fd, char *content, size_t *total_size);
char	*read_file(const char *filename);
char	*append_content(char *content, char *buffer, size_t *size,ssize_t bytes);
void	clean_visited(int **visited);
//A1_clean
void 				clean_node(t_node *node);
void 				clean_graphics(t_game *game);
void 				clean_queue(t_queue *queue);
void 				clean_game(t_game *game);
void	clean_map(char **map);
//A2_load
int	load_map(char *map_file, t_game *game);
void	load_elements(t_game *game);
void	load_tile(t_game *game, int x, int y);
int	load_image(t_game *game, char *file, void **img, char *image_name);
//A3_map
void	get_map_size(char **map, int *height, int *width);
int	is_valid_map(char **map);
int valid_map_elements(char **map);
int valid_map_dimensions(char **map);
int valid_map_borders(char **map);
//A4_accessibility
int	is_accessible(t_game *game);
int	**init_visited(int width, int height);
void	process_node(t_game *game, t_queue *queue, int **visited, t_node *node);
int	is_valid_move(t_game *game, int x, int y, int **visited);
bool steps_remaining(t_queue *queue);
//A5_path
int start_path(t_game *game, t_queue **queue, int ***visited);
void	enqueue(t_queue *queue, int x, int y);
void	dequeue(t_queue *queue, int *x, int *y);
void find_path(t_game *game, t_queue *queue, int **visited,t_node *pos);
void head_direction(t_game *game, t_queue *queue, int **visited,t_node *pos);
//A6_events
void	handle_events(t_game *game);
int	handle_key(int keycode, t_game *game);
void handle_collectible(t_game *game, int x, int y);
int	handle_exit(t_game *game, int x, int y);
int	exit_event(void *param);
//A7_window
int	init_window(t_game *game);
void	render_map(t_game *game);
void	render_tile(t_game *game, int x, int y);
void	render_row(t_game *game, int y);
void    close_game(t_game *game,char *message);
//A8_move
void	move_player(t_game *game, int dx, int dy);
int	is_exit_found(t_game *game, int x, int y);
int valid_tile(char tile);
t_queue	*create_queue(int capacity);
t_node *peek(t_queue *queue) ;
//General
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
void				free_split(char **split_array);

#endif
