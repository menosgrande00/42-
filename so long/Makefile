NAME    = so_long
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

INC_DIR = include
SRC_DIR = src
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
MLX_DIR = mlx
MLX_A = $(MLX_DIR)/libmlx.a

INCS    = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
MLX     = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/map.c \
	$(SRC_DIR)/validate.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/input.c \
	$(SRC_DIR)/anim.c \
	$(SRC_DIR)/enemy.c \
	$(SRC_DIR)/images.c \
	$(SRC_DIR)/utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(MLX_A)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
