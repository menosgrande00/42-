SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

CC = cc
FLAGS = -Wall -Wextra -Werror -L$(PRINTF) -lftprintf
PRINTF = ft_printf

all:
	make -s -C $(PRINTF)
	cc $(FLAGS) server.c -o $(SERVER)
	cc $(FLAGS) client.c -o $(CLIENT)

bonus:
	make -s -C $(PRINTF)
	cc $(FLAGS) server_bonus.c -o $(SERVER_BONUS)
	cc $(FLAGS) client_bonus.c -o $(CLIENT_BONUS)

clean:
	make clean -s -C $(PRINTF)

fclean: clean
	make fclean -s -C $(PRINTF)
	rm -f $(SERVER) $(CLIENT)
	rm -f $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all