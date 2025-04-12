CC			=	cc
CFLAGS	=	-Wall -Werror -Wextra -I./ 
AR			=	ar rcs
RM			=	rm -rf
FILES		=	${wildcard src/*.c}
OBJ			=	$(FILES:.c=.o)
NAME		=	libft.a
LIB			=	libft.h

GREEN		=	\e[38;5;118m
YELLOW	=	\e[38;5;226m
RESET		=	\e[0m
BLUE		=	\033[1;34m
RED      = \033[0;31m
SUCCESS =	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@printf "$(SUCCESS) $(BLUE)libft ready\n"

clean:
	@$(RM) $(OBJ)
	@printf "$(_INFO) $(RED)object files cleaned$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(_INFO) $(RED)archive file is cleaned$(RESET)\n"

re: fclean all

.PHONY: re clean fclean bonus all
.SILENT: $(OBJ)
