NAME			= libftprintf.a

SRCS_DIR		= ./srcs/

OBJS_DIR		= ./objs/

HEADERS_DIR		= ./includes/

SRCS			= $(wildcard $(SRCS_DIR)*.c)

HEADERS			= $(wildcard $(HEADERS_DIR)*.h)

OBJS			= $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

RM				= rm -f


all: $(NAME) 

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
		$(RM) -r $(OBJS_DIR)

fclean: clean
		$(RM) $(NAME)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

re: fclean $(OBJS_DIR) all

.PHONY: all clean fclean re
