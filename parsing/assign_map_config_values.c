#include "../cub3D.h"

void	ft_assign_map_config_values(char **str, t_map_config *map)
{
	size_t(i), (j);
	if (!str || !map)
		ft_exit(-1);
	map->no_texture = ft_split(str[0], ' ')[1];
	map->so_texture = ft_split(str[1], ' ')[1];
	map->we_texture = ft_split(str[2], ' ')[1];
	map->ea_texture = ft_split(str[3], ' ')[1];

	map->floor_color[0] = ft_atoi(ft_split(ft_split(str[4], ' ')[1], ',')[0]);
	map->floor_color[1] = ft_atoi(ft_split(ft_split(str[4], ' ')[1], ',')[1]);
	map->floor_color[2] = ft_atoi(ft_split(ft_split(str[4], ' ')[1], ',')[2]);

	map->ceiling_color[0] = ft_atoi(ft_split(ft_split(str[5], ' ')[1], ',')[0]);
	map->ceiling_color[1] = ft_atoi(ft_split(ft_split(str[5], ' ')[1], ',')[1]);
	map->ceiling_color[2] = ft_atoi(ft_split(ft_split(str[5], ' ')[1], ',')[2]);

	// // ft_remainder_of_func_assign_map_config_values(str, map);

	str = &str[6];

	map->map = str;

	i = -1;
	map->player_y = 0;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == 'N' || str[i][j] == 'S' || str[i][j] == 'E' || str[i][j] == 'W' || str[i][j] == 'D' || str[i][j] == 'O')
			{
				map->player_x = i;
				map->player_y = j;
			}
		}
		if (map->map_width < j)
			map->map_width = j;
	}
	map->map_height = i;
}
