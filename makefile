NAME		=	philo

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror -O0 -g

SRC			=	main.c init_rules.c utils.c start.c time.c fin.c

OBJ			=	$(SRC:.c=.o)
OBJ_BONUS	=	$(SRC_BONUS:.c=.o)

RM		=	rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) -o $(NAME) $^

bonus: $(BONUS_NAME)

%.o:	%.c
			$(CC) $(FLAGS) -o $@ -c $<

clean:
			@$(RM) $(OBJ) 

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re