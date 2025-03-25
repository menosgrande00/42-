NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L./ -lmlx -framework OpenGL -framework AppKit
SRCS = main.c draw.c fractals.c utils.c hooks.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re