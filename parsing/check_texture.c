#include "../cub3D.h"

short	ft_count_len(char **strs, short i)
{
	if (!strs)
		ft_exit(-1);
	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	ft_check_texture_is_valid(t_parsing *data)
{
	data->split = ft_split(data->map[0], ' ');
	if (ft_count_len(data->split, 0) != 2 || ft_strcmp(data->split[0], "NO"))
		ft_print_error("Error\nInvalid texture identifier. Expected 'NO'.\n");
	if (open(data->split[1], O_RDONLY) == -1)
		return (write(2, "Error\nInvalid path for north texture (NO). ", 43),
			ft_print_error("Please provide a valid file path.\n"), 0);
	data->split = ft_split(data->map[1], ' ');
	if (ft_count_len(data->split, 0) != 2 || ft_strcmp(data->split[0], "SO"))
		ft_print_error("Error\nInvalid texture identifier. Expected 'SO'.\n");
	if (open(data->split[1], O_RDONLY) == -1)
		return (write(2, "Error\nInvalid path for south texture (SO). ", 43),
			ft_print_error("Please provide a valid file path.\n"), 0);
	data->split = ft_split(data->map[2], ' ');
	if (ft_count_len(data->split, 0) != 2 || ft_strcmp(data->split[0], "WE"))
		ft_print_error("Error\nInvalid texture identifier. Expected 'WE'.\n");
	if (open(data->split[1], O_RDONLY) == -1)
		return (write(2, "Error\nInvalid path for west texture (WE). ", 42),
			ft_print_error("Please provide a valid file path.\n"), 0);
	data->split = ft_split(data->map[3], ' ');
	if (ft_count_len(data->split, 0) != 2 || ft_strcmp(data->split[0], "EA"))
		ft_print_error("Error\nInvalid texture identifier. Expected 'EA'.\n");
	if (open(data->split[1], O_RDONLY) == -1)
		return (write(2, "Error\nInvalid path for east texture (EA). ", 42),
			ft_print_error("Please provide a valid file path.\n"), 0);
	return (0);
}
