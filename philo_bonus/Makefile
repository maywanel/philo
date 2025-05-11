CC			=	cc
CFLAGS 		= 	-Wall -Werror -Wextra -g -I./
LDFLAGS 	= 	-L../libft -lft
RM			=	rm -rf
FILES		=	${wildcard src/*.c}
OBJ			=	$(FILES:.c=.o)
NAME 		= philo_bonus
LIB			=	philo_bonus.h

GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
BLUE		=	\033[1;34m
RED      = \033[0;31m
SUCCESS 	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

all: make_libft $(NAME)

$(NAME): philo_bonus.c $(LIB) $(OBJ)
	@$(CC) philo_bonus.c -o $(NAME) $(OBJ) $(LDFLAGS)
	@printf "$(SUCCESS) $(BLUE)philo ready\n"

make_libft:
	@make --no-print-directory -C ../libft all;

clean:
	@make --no-print-directory -C ../libft clean;
	@$(RM) $(OBJ)

fclean: clean
	@make --no-print-directory -C ../libft fclean;
	@$(RM) $(NAME)
	@printf "$(_INFO) $(RED)philo is cleaned$(RESET)\n"

re: fclean libft_re all

libft_re:
	@make --no-print-directory -C ../libft re;

.PHONY: re clean fclean bonus all make_libft libft_re
.SILENT: $(OBJ)
