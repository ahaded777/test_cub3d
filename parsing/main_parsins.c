#include "../cub3D.h"

void	ft_init_parsing(t_parsing *data)
{
	data->line = NULL;
	data->split = NULL;
	data->tmp = NULL;
	data->str = NULL;
	data->map = NULL;
}

void	ft_print_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	ft_exit(-1);
}

void	ft_check_map_elements(t_parsing *data)
{
	if (!data)
		ft_exit(-1);
	ft_check_texture_is_valid(data);
	ft_check_floor_color(data, -1, 0);
	ft_check_ceiling_color(data, -1, 0);
	// ft_check_map(&data->map[6], -1, 0, 0);
	ft_check_elements(&data->map[6], -1, 0, ft_count_len(&data->map[6], 0));
}

char	**ft_check_map_errors(char *filename)
{
	t_parsing	data;
	int			len;

	ft_init_parsing(&data);
	data.str = ft_strrchr(filename, '/');
	if (data.str && data.str[0] == '/' && data.str[1] && data.str[1] == '.')
		filename = data.str;
	len = ft_strlen(filename);
	if ((len < 5) || (ft_strcmp(&filename[len - 4], ".cub") != 0))
	{
		write(2, "Error\nInvalid map file name. ", 29);
		ft_print_error("Please use a valid file, like map.cub\n");
	}
	data.fd = open(filename, O_RDONLY);
	if (data.fd == -1)
		ft_print_error("Error\nError opening file map\n");
	ft_read_map_file(&data);
	if (ft_count_len(data.map, 0) < 9)
		ft_print_error("Error\nInvalid map.\n");
	ft_check_map_elements(&data);
	return (data.map);
}
