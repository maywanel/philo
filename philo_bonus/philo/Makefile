NAME = philo

CC = cc

CFLAGS =  -Wall -Wextra -Werror  -g3 -pthread -fsanitize=thread 


SRCS = src/clean_error.c  src/dinner.c  src/dinner_utils.c  src/dinner_utlis_2.c  src/init.c  src/parsing.c  src/utils.c philo.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS)  $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	
fclean:
	rm -rf $(OBJS) $(NAME)

re: fclean all clean

.PHONY: all clean fclean re
