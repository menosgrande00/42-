# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 12:29:23 by omerfarukon       #+#    #+#              #
#    Updated: 2024/12/03 23:32:49 by omerfarukon      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS =  ft_printf.c \
		ft_printf_utils.c

FLAGS = -c -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(SRCS)
	ar -rc $(NAME) $(OBJS)

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re