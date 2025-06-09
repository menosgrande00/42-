NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_PATH = mlx_mac
MLX_LIB = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

GNL_PATH = get_nextline
PRINTF_PATH = ft_printf

GNL_LIBFT = libft
GNL_LIBFT_PATH = ./libft/libft.a


SRCS =	main.c \
		map_reader.c \
		moves_key.c \
		draw.c \
		load_character.c \
		load_attack.c \
		load_enemy.c \
		load_zone_enemy.c \
		load_zone_character.c \
		memory_for_init.c \
		time.c \
		checkers.c \
		checkers2.c \
		checkers3.c \
		checkers4.c \
		checkers5.c \
		checkers6.c \
		utils.c \
		map_reader_utils.c \
		bonus_utils.c \
		attack.c \
		attack_direction.c \
		radar.c \
		enemies.c \
		$(GNL_PATH)/get_next_line.c \
		$(GNL_PATH)/get_next_line_utils.c \
		$(PRINTF_PATH)/ft_printf.c \
		$(PRINTF_PATH)/ft_printf_utils.c


OBJS = $(SRCS:.c=.o)

all: $(MLX_LIB) $(GNL_LIBFT_PATH) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS) $(MLX_FLAGS) $(GNL_LIBFT_PATH)

$(MLX_LIB):
	make -C $(MLX_PATH)

$(GNL_LIBFT_PATH):
	make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(MLX_PATH) clean
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all
