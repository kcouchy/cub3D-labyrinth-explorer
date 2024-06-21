NAME := cub3D

CC := cc
CFLAGS		= -g -Wall -Wextra -Werror
CLINKS		= -ldl -lglfw -pthread -lm
MLX			= minilibx
LIBMLX 		= $(MLX)/libmlx42.a

FT			= Libft
LIBFT		= $(FT)/libft.a

SOURCE :=	main.c						\
			get_inputs/check_map.c		\
			get_inputs/error.c			\
			get_inputs/get_colours.c	\
			get_inputs/get_map.c		\
			get_inputs/get_textures.c	\
			get_inputs/gnl_utils.c		\
			get_inputs/gnl.c			\
			get_inputs/parse_input.c	\
			get_inputs/parse_map.c		\
			build_maze/draw_wall.c		\
			build_maze/find_intercept.c	\
			build_maze/minimap.c		\
			build_maze/movements.c		\
			build_maze/raycast.c		\
			build_maze/texture.c

OBJ 	= $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(LIBMLX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBMLX) $(CLINKS)

$(LIBMLX): $(MLX)
	cmake $(MLX) -B $(MLX)	
	$(MAKE) -C $(MLX)
	
$(LIBFT): $(FT)
	$(MAKE) -C $(FT)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
		make clean -C $(MLX)
		rm -rf $(NAME)

re: fclean all

.PHONY:		all clean fclean re
