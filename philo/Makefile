CC			=	cc
CFLAGS 		= 	-Wall -Werror -Wextra -g -I./
RM			=	rm -rf
FILES		=	${wildcard src/*.c}
OBJ			=	$(FILES:.c=.o)
NAME 		= 	philo
LIB			=	philo.h

GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
BLUE		=	\033[1;34m
RED      = \033[0;31m
SUCCESS 	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

all: $(NAME)

$(NAME): philo.c $(LIB) $(OBJ)
	@$(CC) philo.c -o $(NAME) $(OBJ)
	@printf "$(SUCCESS) $(BLUE)philo ready\n"

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
	@printf "$(_INFO) $(RED)philo is cleaned$(RESET)\n"

re: fclean all

.PHONY: re clean fclean all 
.SILENT: $(OBJ)
