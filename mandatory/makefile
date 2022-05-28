NAME		=	philo

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror 

SRC	=	main.c init_rules.c utils.c thread_starting.c utils_proc.c

OBJ			=	$(SRC:.c=.o)

RM		=	rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) -o $(NAME) $^

%.o:	%.c
			$(CC) $(FLAGS) -o $@ -c $<

clean:
			@$(RM) $(OBJ) 

fclean:		clean
			@$(RM) $(NAME) 

re:			fclean all

.PHONY:		all clean fclean re