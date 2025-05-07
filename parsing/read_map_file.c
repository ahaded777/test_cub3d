#include "../cub3D.h"

void	ft_map_for_exomple(void)
{
	printf("Error\nMissing blank line before the map layout. A newline");
	printf(" is required between texture/color definitions and the map.\n");
	printf("Expected format:\n\nNO ./path_to_the_north_texture\n");
	printf("SO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\n");
	printf("EA ./path_to_the_east_texture\n\nF 220,100,0\nC 225,30,0\n");
	printf("1111111111111111\n1000N00000000011\n1111111111111111\n");
	ft_exit(-1);
}

void	ft_read_map_file(t_parsing *data)
{
	int	i;

	if (!data)
		ft_exit(-1);
	ft_init_parsing(data);
	i = 1;
	while (1)
	{
		data->line = get_next_line(data->fd);
		if (!data->line && i != 1)
			break ;
		if ((!data->line || data->line[0] == '\n') && i != 5 && i != 8)
		{
			printf("Error\nEmpty line detected at line [%d].\n", i);
			ft_exit(-1);
		}
		if ((i == 5 || i == 8) && data->line[0] != '\n')
			ft_map_for_exomple();
		data->tmp = ft_strjoin(data->str, data->line);
		if (!data->tmp)
			ft_print_error("Error\nFailed to read the file.\n");
		data->str = data->tmp;
		i++;
	}
	data->map = ft_split(data->str, '\n');
}
