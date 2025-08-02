NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I $(SRC_DIR) -I \
		$(ENV_DIR) -I $(EXECUTOR_DIR) -I $(PARSER_DIR) -I \
		$(SIGNAL_DIR) -I $(UTILS_DIR) -I $(LIBFT_DIR) \
		-I include/ -I/opt/homebrew/opt/readline/include

HEADERS =	include/minishell.h \
			src/parser/parser.h \
			src/env/environment.h \
			include/errors.h \
            src/executor/executor.h


SRC_DIR = src/

ERRORS_DIR = src/errors/

ENV_DIR = src/env/

EXECUTOR_DIR = src/executor/

PARSER_DIR = src/parser/

SIGNAL_DIR = src/signals/

UTILS_DIR = src/utils/

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

SRCS =	$(SRC_DIR)/main.c \
        $(EXECUTOR_DIR)/builtin.c \
		$(EXECUTOR_DIR)/builtin_2.c \
        $(EXECUTOR_DIR)/exec_cmd.c \
        $(EXECUTOR_DIR)/exec_cmd_2.c \
        $(EXECUTOR_DIR)/redirection.c \
		$(EXECUTOR_DIR)/pipe.c \
		$(EXECUTOR_DIR)/executor_utils.c \
		$(EXECUTOR_DIR)/files.c \
        $(PARSER_DIR)/parser.c \
        $(PARSER_DIR)/syntax.c \
        $(PARSER_DIR)/quotes.c \
		$(PARSER_DIR)/double_quotes.c \
		$(PARSER_DIR)/dollar_in_quotes.c \
		$(PARSER_DIR)/handle_after_quote.c \
		$(PARSER_DIR)/handle_quote_merging.c \
        $(PARSER_DIR)/tokenizer.c \
		$(PARSER_DIR)/tok_is_that_word.c \
		$(ENV_DIR)/environment.c \
		$(ENV_DIR)/export.c \
        $(SIGNAL_DIR)/signal.c \
		$(SIGNAL_DIR)/signal_utils.c \
		$(ERRORS_DIR)/errors.c \
        $(UTILS_DIR)/utils.c

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
