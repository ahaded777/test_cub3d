#include "../cub3D.h"

int	ft_check_floor_color(t_parsing *data, int i, int len)
{
	if (!data)
		ft_exit(-1);
	data->split = ft_split(data->map[4], ' ');
	if (ft_count_len(data->split, 0) != 2 || ft_strcmp(data->split[0], "F"))
		return (write(2, "Error\nInvalid floor color. Expected: ", 37)
			, ft_print_error("F R,G,B (e.g. F 220,100,0)\n"), 0);
	while (data->split && data->split[1][++i])
	{
		if (data->split[1][i] == ',' && data->split[1][i + 1]
			&& data->split[1][i + 1] == ',')
			return (write(2, "Error\nfloor color format error — ", 33),
				ft_print_error("double comma found.\n"), 0);
		if (data->split[1][i] == ',')
			len++;
	}
	data->split = ft_split(data->split[1], ',');
	if (len != 2 || ft_count_len(data->split, 0) != 3)
		return (write(2, "Error\nInvalid floor color — repeated ,detected.", 49)
			, ft_print_error(" Format must be: F R,G,B.\n"), 0);
	if (ft_atoi(data->split[0]) == -1 || ft_atoi(data->split[1]) == -1
		|| ft_atoi(data->split[2]) == -1)
		return (write(2, "Error\nFloor color must contain only ", 36),
			ft_print_error("integers. Invalid characters detected.\n"), 0);
	return (0);
}

int	ft_check_ceiling_color(t_parsing *data, int i, int len)
{
	data->split = ft_split(data->map[5], ' ');
	if (ft_count_len(data->split, 0) != 2 || ft_strcmp(data->split[0], "C"))
	{
		write(2, "Error\nInvalid ceiling color format. Expected: ", 46);
		ft_print_error("C R,G,B (e.g. C 225,30,0).\n");
	}
	while (data->split && data->split[1][++i])
	{
		if (data->split[1][i] == ',' && data->split[1][i + 1]
			&& data->split[1][i + 1] == ',')
			return (write(2, "Error\nCeiling color format error", 32),
				ft_print_error(" — double comma found.\n"), 0);
		if (data->split[1][i] == ',')
			len++;
	}
	data->split = ft_split(data->split[1], ',');
	if (len != 2 || ft_count_len(data->split, 0) != 3)
		return (write(2, "Error\nCeiling color format error — double ','", 47)
			, ft_print_error(" found. Expected: C R,G,B.\n"), 0);
	if (ft_atoi(data->split[0]) == -1 || ft_atoi(data->split[1]) == -1
		|| ft_atoi(data->split[2]) == -1)
		return (write(2, "Error\nCeiling color must contain only integers.", 47)
			, ft_print_error(" Invalid characters detected.\n"), 0);
	return (0);
}
