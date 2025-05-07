#include "cub3D.h"


int main(int ac, char *av[])
{
    // (void)av;
    t_map_config map;
    memset(&map, 0, sizeof(map));
    // t_game g;

    if (ac != 2)
    {
        write (2, "Error\nMap not found — please ensure the map is", 48);
        write(2, " correctly defined and follows the required format.\n", 52);
        exit (-1);
    }
    ft_assign_map_config_values(ft_check_map_errors(av[1]), &map);
    raycasting(&map);
    return (0);
}