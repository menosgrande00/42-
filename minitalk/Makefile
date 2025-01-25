SERVER = server
CLIENT = client

CFLAGS = -Wall -Werror -Wextra
CC = cc
FLAGS = -Wall -Wextra -Werror -L$(PRINTF) -lftprintf

PRINTF = ft_printf

all:
	@make -s -C $(PRINTF)
	@cc $(FLAGS) server.c -o $(SERVER)
	@cc $(FLAGS) client.c -o $(CLIENT)

clean:
	@make clean -s -C $(PRINTF)

fclean: clean
	@make fclean -s -C $(PRINTF)
	@rm -f $(SERVER) $(CLIENT)

re: fclean all