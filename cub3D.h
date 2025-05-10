#ifndef CUB3D_H
# define CUB3D_H

# include "./GarbageCollector/malloc.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
#include <stdbool.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <unistd.h>
#include <math.h>
# include "./cute_sound/cute_sound.h"

# define WIDTH 1280
# define HEIGHT 6 * BLOCK
# define BLOCK 100
# define SPEED_CAMERA 0.04
# define SPEED_PLAYER 4
# define FOV (M_PI * (70.0 / 180.0))
# define BUFFER_SIZE 1
# define ESC_KEY 65307
# define W 119
# define A 97
# define S 115
# define D 100
#define SPACE 32
#define KEY_LEFT 123
#define KEY_RIGHT 124
# define LEFT 65361
# define RIGHT 65363

typedef struct s_parsing
{
	int			fd;
	char		*line;
	char		*tmp;
	char		*str;
	char		**split;
	char		**map;
    double      x;
    double      y;
	bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool left_rotate;
    bool right_rotate;
}			t_parsing;

typedef struct s_textures
{
	void *wall_img;
	void *door_img;
	void *img;
	int wall_width;
	int wall_height;
	int door_width;
	int door_height;
} t_textures;


typedef struct s_map_config
{
    char		*no_texture;
    char		*so_texture;
    char		*we_texture;
    char		*ea_texture;
    int     	floor_color[3];
    int     	ceiling_color[3];
    char    	**map;
    void	*mlx;
	void	*win;
	char *data_pixel;
    int bpp;
    int size_line;
    int endian;
	void	*img;
	void	*img_w1;
	float ray_salib;
	float ray_mojab;
	float dx;
	float dy;
	float angle;
    int				img_width;
	int				img_height;
    int open_door;
    int close_door;
    int x_door;
    int y_door;
    int close_kay;
    // cs_sound_params_t theme_params;
    // cs_sound_params_t *sound_track;
    t_parsing player;
    size_t     	map_width;
    size_t     	map_height;
    size_t       	player_x;
    size_t       	player_y;
    t_textures      textures;
}   t_map_config;

// typedef struct s_game {
// 	void	*mlx;
// 	void	*win;
// 	char *data_pixel;
//     int bpp;
//     int size_line;
//     int endian;
// 	void	*img;
// 	float ray_salib;
// 	float ray_mojab;
// 	float dx;
// 	float dy;
// 	float angle;
// 	t_parsing player;
//     t_map_config data;
// }	t_game;

char		*get_next_line(int fd);
char		**ft_check_map_errors(char *filename);
void		ft_print_error(char *str);
short	ft_count_len(char **strs, short i);
int	ft_check_texture_is_valid(t_parsing *data);
int	ft_check_floor_color(t_parsing *data, int i, int len);
int	ft_check_ceiling_color(t_parsing *data, int i, int len);
void	ft_check_map(char **map, int i, int j, int player);
void	ft_check_elements(char **map, int i, int j, int len);
void	ft_read_map_file(t_parsing *data);
void	ft_init_parsing(t_parsing *data);
void	ft_assign_map_config_values(char **str, t_map_config *map);



void init(t_map_config *g);
int draw_map(t_map_config *g);
int draw_loop(t_map_config *game);
int key_press(int keycode, t_map_config *g);
int key_release(int keycode, t_map_config *g);
int raycasting(t_map_config *map);
#endif
