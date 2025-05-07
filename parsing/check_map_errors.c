#include "../cub3D.h"

int	ft_cheh_is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D' || c == 'O')
		return (1);
	return (0);
}

void	ft_check_map(char **map, int i, int j, int player)
{
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_cheh_is_player(map[i][j]) && map[i][j] != '1'
				&& map[i][j] != '0' && map[i][j] != ' ')
			{
				write(2, "Error\nInvalid character found. Only '1', '0', ", 46);
				ft_print_error("'N', 'S', 'E', 'W', and space are allowed.\n");
			}
			if (ft_cheh_is_player(map[i][j]))
				player++;
		}
	}
	if (player != 1)
	{
		write(2, "Error\nThere must be exactly one player starting position ",
			57);
		ft_print_error("('N', 'S', 'E', or 'W') in the map.\n");
	}
}

void	ft_check_elements(char **map, int i, int j, int len)
{
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || ft_cheh_is_player(map[i][j]))
			{
				if (i == 0 || j == 0 || i == len - 1 || j == ft_strlen(map[i])
					- 1 || !map[i][j + 1] || map[i][j + 1] == ' ' || map[i][j
					- 1] == ' ' || !map[i + 1][j] || map[i + 1][j] == ' '
					|| map[i - 1][j] == ' ' || ft_strlen(map[i + 1]) < j + 1
					|| ft_strlen(map[i - 1]) < j + 1)
				{
					printf("Error\nMap is not closed around (%d,%d).\n", i + 9,
						j + 1);
					ft_exit(-1);
				}
			}
		}
	}
}
