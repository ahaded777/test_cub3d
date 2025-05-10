#include "../cub3D.h"

void init_player(t_map_config *g);

void init(t_map_config *g)
{
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3D");
	mlx_mouse_hide(g->mlx, g->win);
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->data_pixel = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	g->textures.wall_img = mlx_xpm_file_to_image(g->mlx, "./wall.xpm", &g->textures.wall_width, &g->textures.wall_height);
	g->textures.img = mlx_xpm_file_to_image(g->mlx, "./gg.xpm", &g->textures.wall_width, &g->textures.wall_height);
	g->textures.door_img = mlx_xpm_file_to_image(g->mlx, "./door.xpm", &g->textures.door_width, &g->textures.door_height);
	init_player(g);
}

void put_pixel(int x, int y, int color, t_map_config *g)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	int index = y * g->size_line + x * (g->bpp / 8);
	g->data_pixel[index] = color & 0xFF;
	g->data_pixel[index + 1] = (color >> 8) & 0xFF;
	g->data_pixel[index + 2] = (color >> 16) & 0xFF;
}

int get_pixel_color(void *img, int x, int y)
{
	char *data;
	int bpp, size_line, endian;
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	int index = y * size_line + x * (bpp / 8);
	int color = *(int *)(data + index);
	return color;
}

void draw_tile(t_map_config *g, int x, int y, int color)
{
	for (int i = 0; i < BLOCK; i++)
	{
		for (int j = 0; j < BLOCK; j++)
		{
			put_pixel(x + j, y + i, color, g);
		}
	}
}

void init_player(t_map_config *g)
{
	for (int i = 0; g->map[i]; i++)
	{
		for (int j = 0; g->map[i][j]; j++)
		{
			if (g->map[i][j] == 'W' || g->map[i][j] == 'N' ||
				g->map[i][j] == 'S' || g->map[i][j] == 'E')
			{
				g->player.x = j * BLOCK + BLOCK / 2;
				g->player.y = i * BLOCK + BLOCK / 2;
				if (g->map[i][j] == 'N')
					g->angle = -M_PI / 2;
				else if (g->map[i][j] == 'S')
					g->angle = M_PI / 2;
				else if (g->map[i][j] == 'W')
					g->angle = M_PI;
				else if (g->map[i][j] == 'E')
					g->angle = 0;
				g->map[i][j] = '0';
				return;
			}
		}
	}
}

void draw_player(t_map_config *g)
{
	// printf("map: %c\n", (g->map[(int)(g->player.y / BLOCK) - 1][(int)(g->player.x / BLOCK)]));
	// printf("y: %d\n, y_t: %d\n", (y / BLOCK), (y / BLOCK) + 1);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			put_pixel(g->player.x + j, g->player.y + i, 255, g);
		}
	}
}

int draw_map(t_map_config *g)
{
	for (int i = 0; g->map[i]; i++)
	{
		for (int j = 0; g->map[i][j]; j++)
		{
			if (g->map[i][j] == '1')
				draw_tile(g, j * BLOCK, i * BLOCK, 0x0000FF);
			else if (g->map[i][j] == '0')
				draw_tile(g, j * BLOCK, i * BLOCK, 0x000000);
			else if (g->map[i][j] == 'D')
				draw_tile(g, j * BLOCK, i * BLOCK, 0x00FF00);
		}
	}
	draw_player(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	return (0);
}

int key_press(int keycode, t_map_config *g)
{
	if (keycode == ESC_KEY)
		exit(0);
	if (keycode == SPACE && g->open_door == 1 && g->close_kay == 0)
	{
		if (g->map[(int)((g->player.y + 80) / BLOCK)][(int)(g->player.x / BLOCK)] == 'D')
			g->map[(int)(g->player.y / BLOCK) + 1][(int)(g->player.x / BLOCK)] = 'O';
		else if (g->map[(int)(g->player.y / BLOCK) - 1][(int)(g->player.x / BLOCK)] == 'D')
			g->map[(int)(g->player.y / BLOCK) - 1][(int)(g->player.x / BLOCK)] = 'O';
	}
	if (keycode == SPACE && g->close_door == 1 && g->close_kay == 0)
	{
		if (g->map[(int)((g->player.y) / BLOCK) + 1][(int)(g->player.x / BLOCK)] == 'O')
			g->map[(int)(g->player.y / BLOCK) + 1][(int)(g->player.x / BLOCK)] = 'D';
		else if (g->map[(int)(g->player.y / BLOCK) - 1][(int)(g->player.x / BLOCK)] == 'O')
			g->map[(int)(g->player.y / BLOCK) - 1][(int)(g->player.x / BLOCK)] = 'D';
	}
	else if (keycode == A)
	{
		g->close_kay = 1;
		g->player.key_left = true;
	}
	else if (keycode == D)
	{
		g->close_kay = 1;
		g->player.key_right = true;
	}
	else if (keycode == W)
	{
		g->close_kay = 1;
		g->player.key_up = true;
	}
	else if (keycode == S)
	{
		g->close_kay = 1;
		g->player.key_down = true;
	}
	else if (keycode == LEFT)
		g->player.left_rotate = true;
	else if (keycode == RIGHT)
		g->player.right_rotate = true;
	return (0);
}

int key_release(int keycode, t_map_config *g)
{
	if (keycode == A)
	{
		g->close_kay = 0;
		g->player.key_left = false;
	}
	else if (keycode == D)
	{
		g->close_kay = 0;
		g->player.key_right = false;
	}
	else if (keycode == W)
	{
		g->close_kay = 0;
		g->player.key_up = false;
	}
	else if (keycode == S)
	{
		g->close_kay = 0;
		g->player.key_down = false;
	}
	else if (keycode == LEFT)
		g->player.left_rotate = false;
	else if (keycode == RIGHT)
		g->player.right_rotate = false;
	return (0);
}

int mo_player(t_map_config *g)
{
	double cos_angle = cos(g->angle);
	double sin_angle = sin(g->angle);
	// printf("map: %c\n", g->map[(int)(cos_angle / 2)][(int)(sin_angle / 2)]);
	double old_x = g->player.x;
	double old_y = g->player.y;
	if (g->player.left_rotate)
		g->angle -= SPEED_CAMERA;
	if (g->player.right_rotate)
		g->angle += SPEED_CAMERA;
	if (g->player.key_up)
	{
		g->player.x += cos_angle * (double)(SPEED_PLAYER);
		g->player.y += sin_angle * (double)(SPEED_PLAYER);
	}
	if (g->player.key_down)
	{
		g->player.x -= cos_angle * (double)(SPEED_PLAYER);
		g->player.y -= sin_angle * (double)(SPEED_PLAYER);
	}
	if (g->player.key_left)
	{
		g->player.x += sin_angle * (double)(SPEED_PLAYER);
		g->player.y -= cos_angle * (double)(SPEED_PLAYER);
	}
	if (g->player.key_right)
	{
		g->player.x -= sin_angle * (double)(SPEED_PLAYER);
		g->player.y += cos_angle * (double)(SPEED_PLAYER);
	}
	// printf("c: %c\n", g->map[(int)((g->player.y - 60) / BLOCK) + 1][(int)(g->player.x / BLOCK)]);
	if ((g->map[(int)((g->player.y - 82) / BLOCK) + 1][(int)(g->player.x / BLOCK)] == '1') || (g->map[(int)((g->player.y - 82) / BLOCK) + 1][(int)(g->player.x / BLOCK)] == 'D') || (g->map[(int)((g->player.y + 99) / BLOCK) - 1][(int)(g->player.x / BLOCK)] == 'D') || (g->map[(int)((g->player.y + 99) / BLOCK) - 1][(int)(g->player.x / BLOCK)] == '1') || (g->map[(int)((g->player.y) / BLOCK)][(int)((g->player.x - 80) / BLOCK) + 1] == '1'))
	{

		g->player.x = old_x;
		g->player.y = old_y;
	}
	draw_map(g);
	return (0);
}

void clear_image(t_map_config *game)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0, game);
}

// void draw_s(t_map_config *game)
// {
// 	double wall_height = (BLOCK * HEIGHT) / (distance * cos((angle - game->angle)));
// 	double start_y = (HEIGHT / 2) - (wall_height / 2);
// 	double end_y = (HEIGHT / 2) + (wall_height / 2);
// 	for (double y = start_y; y < end_y; y++)
// 	{
// 		put_pixel(test_x, y, 0xFF0000, game);
// 	}
// }

// int color(int *color)
// {
// 	int r = (color[0] >> 16) & 0xFF;
// 	int g = (color[1] >> 8) & 0xFF;
// 	int b = color[2] & 0xFF;
// 	return (r << 16) | (g << 8) | b;
// }

int apply_distance_shading(int color, double distance);

int draw_loop(t_map_config *game)
{
	mo_player(game);
	game->ray_salib = game->angle - FOV / 2;
	game->ray_mojab = game->angle + FOV / 2;
	clear_image(game);
	int screen_x = 0;
	for (double angle = game->ray_salib; angle < game->ray_mojab; angle += FOV / (double)(WIDTH))
	{
		int hit_wall = 0;
		int hit_door = 0;
		double distance = 0.0;
		double ray_x = game->player.x + 10;
		double ray_y = game->player.y + 10;
		game->dx = cos(angle);
		game->dy = sin(angle);
		int j = 0;
		while (j < WIDTH)
		{
			double x = ray_x + j * game->dx;
			double y = ray_y + j * game->dy;
			int map_x = x / BLOCK;
			int map_y = y / BLOCK;
			int map_y_test = ((int)(y)-0.001) / BLOCK;
			if ((game->map[map_y][map_x] == '1' || game->map[map_y_test][map_x] == '1') || game->map[map_y][map_x] == 'D')
			{
				if ((game->map[map_y][map_x] == '1' || game->map[map_y_test][map_x] == '1'))
					hit_wall = 1;
				else if (game->map[map_y][map_x] == 'D')
					hit_door = 1;
				break;
			}
			// put_pixel(x, y, 0xFF0000, game);
			distance++;
			j++;
		}
		double start_y1 = HEIGHT / 2;
		double end_y1 = 0;
		for (double y = start_y1; y > end_y1; y--)
		{
			put_pixel(screen_x, y, 0x87CEEB, game);
		}
		double start_y2 = HEIGHT / 2;
		double end_y2 = WIDTH;
		for (double y = start_y2; y < end_y2; y++)
		{
			put_pixel(screen_x, y, 0x000000, game);
		}
		double wall_height = (BLOCK * HEIGHT) / (distance * cos(angle - game->angle));
		double start_y = (HEIGHT / 2) - (wall_height / 2);
		double end_y = (HEIGHT / 2) + (wall_height / 2);
		double hit_x = ray_x + j * game->dx;
		double hit_y = ray_y + j * game->dy;
		double wall_x = 0.0;
		if (fabs(hit_x / BLOCK - (int)(hit_x / BLOCK)) < 0.01 ||
			fabs(hit_x / BLOCK - (int)(hit_x / BLOCK) - 1) < 0.01)
			wall_x = hit_y;
		else
			wall_x = hit_x;
		wall_x = fmod(wall_x, BLOCK) / BLOCK;
		int tex_x = 0;
		if (hit_wall)
			tex_x = (int)(wall_x * game->textures.wall_height);
		else if (hit_door)
			tex_x = (int)(wall_x * game->textures.door_width);
		for (double y = start_y; y < end_y; y++)
		{
			double tex_pos = ((y - start_y) / (end_y - start_y));
			int tex_y = 0;
			int color = 0;
			if (hit_wall)
			{
				if (fabs(hit_x / BLOCK - (int)(hit_x / BLOCK)) < 0.01 ||
					fabs(hit_x / BLOCK - (int)(hit_x / BLOCK) - 1) < 0.01)
				{
					// if (game->dx > 0)
					// {
					// 	tex_y = (int)(tex_pos * game->textures.wall_height);
					// 	color = get_pixel_color(game->textures.wall_img, tex_x, tex_y);
					// }
					// else
					// {
						tex_y = (int)(tex_pos * game->textures.wall_height);
						color = get_pixel_color(game->textures.img, tex_x, tex_y);
					// }
				}
				else
				{
					// if (game->dy > 0)
					// {
					// 	tex_y = (int)(tex_pos * game->textures.wall_height);
					// 	color = get_pixel_color(game->textures.wall_img, tex_x, tex_y);
					// }
					// else
					// {
						tex_y = (int)(tex_pos * game->textures.wall_height);
						color = get_pixel_color(game->textures.wall_img, tex_x, tex_y);
					// }
				}
			}
			else if (hit_door)
			{
				tex_y = (int)(tex_pos * game->textures.door_height);
				color = get_pixel_color(game->textures.door_img, tex_x, tex_y);
			}
			color = apply_distance_shading(color, distance);
			put_pixel(screen_x, y, color, game);
		}
		screen_x++;
	}
	game->open_door = 0;
	game->close_door = 0;
	if ((game->map[(int)(game->player.y / BLOCK) + 1][(int)(game->player.x / BLOCK)] == 'D') || (game->map[(int)(game->player.y / BLOCK) - 1][(int)(game->player.x / BLOCK)] == 'D'))
		game->open_door = 1;
	if ((game->map[(int)(game->player.y / BLOCK) + 1][(int)(game->player.x / BLOCK)] == 'O') || (game->map[(int)(game->player.y / BLOCK) - 1][(int)(game->player.x / BLOCK)] == 'O'))
		game->close_door = 1;
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}

int apply_distance_shading(int color, double distance)
{
	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;
	double shade_factor = 1.0 - fmin(distance / (WIDTH * 0.8), 0.8);
	r = (int)(r * shade_factor);
	g = (int)(g * shade_factor);
	b = (int)(b * shade_factor);
	return (r << 16) | (g << 8) | b;
}

int mouse_move(int x, int y, t_map_config *g)
{
	(void)y;
	g->angle += (x - WIDTH / 2) * 0.0001;
	mlx_mouse_move(g->mlx, g->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

int raycasting(t_map_config *map)
{
	init(map);
	// draw_map(map);
	// for (int i = 0; i < 10; i++)
	// {
	// 	for (int j = 0; j < 10; j++)
	// 	{
	// 		put_pixel(j / 2, i / 2, 255, map);
	// 	}
	// }
	// cs_sound_params_t theme_params;
	// cs_audio_source_t *sound_track;
	// sound_track = cs_load_wav("/home/aahaded/Desktop/cub3d/resources/e1m1.wav", NULL);
	// theme_params = cs_sound_params_default();
	// cs_play_sound(sound_track, theme_params);
	// mlx_mouse_move(map->mlx, map->win, WIDTH / 2, HEIGHT / 2);
	mlx_hook(map->win, MotionNotify, PointerMotionMask, mouse_move, map);
	mlx_loop_hook(map->mlx, draw_loop, map);
	mlx_hook(map->win, KeyPress, KeyPressMask, key_press, map);
	mlx_hook(map->win, KeyRelease, KeyReleaseMask, key_release, map);
	mlx_loop(map->mlx);
	return (0);
}
