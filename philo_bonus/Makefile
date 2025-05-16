NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -pthread -fsanitize=address

SRCS = src/clean.c src/dinner.c src/dinner_utils2.c src/dinner_utils.c \
	src/init.c src/init_utils.c src/parsing.c src/utils2.c src/utils.c \
	philo_bonus.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re
