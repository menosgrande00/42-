NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I $(SRC_DIR) -I \
		$(ENV_DIR) -I $(EXECUTOR_DIR) -I $(PARSER_DIR) -I \
		$(SIGNAL_DIR) -I $(UTILS_DIR) -I $(LIBFT_DIR) \
		-I include/ -I/opt/homebrew/opt/readline/include

HEADERS =	include/minishell.h \
			src/parser/parser.h \
			src/env/environment.h \
            src/executor/executor.h


SRC_DIR = src/

ENV_DIR = src/env/

EXECUTOR_DIR = src/executor/

PARSER_DIR = src/parser/

SIGNAL_DIR = src/signals/

UTILS_DIR = src/utils/

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

# Ana kaynak dosyaları
SRCS =	$(SRC_DIR)/main.c \
        $(SRC_DIR)/prompt.c \
        $(EXECUTOR_DIR)/builtin.c \
		$(EXECUTOR_DIR)/builtin_2.c \
        $(EXECUTOR_DIR)/exec_cmd.c \
        $(EXECUTOR_DIR)/exec_cmd_2.c \
        $(EXECUTOR_DIR)/redirection.c \
		$(EXECUTOR_DIR)/pipe.c \
		$(EXECUTOR_DIR)/executor_utils.c \
        $(PARSER_DIR)/parser.c \
        $(PARSER_DIR)/syntax.c \
        $(PARSER_DIR)/quotes.c \
		$(PARSER_DIR)/double_quotes.c \
        $(PARSER_DIR)/tokenizer.c \
		$(ENV_DIR)/environment.c \
		$(ENV_DIR)/export.c \
        $(SIGNAL_DIR)/signal.c \
        $(UTILS_DIR)/utils.c

# Şimdilik devre dışı bırakılan env dosyaları
# SRCS +=	$(ENV_DIR)/expand.c \
#			$(ENV_DIR)/export.c \
#			$(ENV_DIR)/env_utils.c \
#			$(ENV_DIR)/env_utils_2.c

OBJS = $(SRCS:.c=.o)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

$(NAME) : $(LIBFT) $(PRINTF) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -L/opt/homebrew/opt/readline/lib -lreadline

clean :
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean : clean
	rm -rf $(NAME)
	rm -rf $(OBJS)
	rm -rf $(LIBFT_DIR)libft.a

re: fclean all