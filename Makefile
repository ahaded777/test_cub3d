MLX_DIR = mlx
MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11

SRC = cub3D.c parsing/*.c libft/*.c Raycasting/*.c GarbageCollector/*.c libft/get_next_line/*.c

all:
	gcc -Wall -Wextra -Werror -g  $(SRC) $(MLX_FLAGS) -lm 

clean:
	rm -f parsing/*.o libft/*.o Raycasting/*.o GarbageCollector/*.o libft/get_next_line/*.o

fclean: clean
	rm -f ./a.out

re: fclean all


#-g3 -fsanitize=address