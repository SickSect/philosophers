NAME		=	philo
NAME_BONUS	=	philo_bonus

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror -O0 -g

SRC			=	mandatory/main.c mandatory/init_rules.c \
				mandatory/utils.c mandatory/thread_starting.c \
				mandatory/utils_proc.c
SRC_BONUS	=	bonus/main_bonus.c bonus/init_rules_bonus.c \
				bonus/utils_bonus.c bonus/thread_starting_bonus.c \
				bonus/utils_proc_bonus.c

OBJ			=	$(SRC:.c=.o)
OBJ_BONUS	=	$(SRC_BONUS:.c=.o)

RM		=	rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) -o $(NAME) $^
$(NAME_BONUS):	$(OBJ_BONUS)
			$(CC) $(FLAGS) -o $(NAME_BONUS) $^

bonus: $(NAME_BONUS)

%.o:	%.c
			$(CC) $(FLAGS) -o $@ -c $<

clean:
			@$(RM) $(OBJ) $(OBJ_BONUS)

fclean:		clean
			@$(RM) $(NAME) $(NAME_BONUS)

re:			fclean all

.PHONY:		all clean fclean re