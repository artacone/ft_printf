# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvertie <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/12 21:13:42 by rvertie           #+#    #+#              #
#    Updated: 2021/04/22 14:45:21 by rvertie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libftprintf.a

SRCS			= $(wildcard *.c)

HEADERS			= libft.h

OBJS			= ${SRCS:.c=.o}

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

RM				= rm -f


all: $(NAME) 

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) 
	ar rcs $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
