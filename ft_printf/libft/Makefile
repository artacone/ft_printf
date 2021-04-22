# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvertie <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/12 21:13:42 by rvertie           #+#    #+#              #
#    Updated: 2021/04/16 19:48:50 by rvertie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a

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
