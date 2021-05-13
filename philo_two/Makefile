SRCS =			life.c \
				death.c \
				utils.c \
				ft_atoi.c \

OBJS =			$(SRCS:.c=.o)

GCC = 			gcc

FLAGS =			-Wall -Wextra -Werror

NAME =			philo_two

%.o:			%.c
				@ $(GCC) -c $(FLAGS) $< -o $(<:.c=.o)

all: 			$(NAME)

$(NAME):		$(OBJS)
				$(GCC) -o $(NAME) $(OBJS)

clean:
				rm -f $(OBJS)

fclean:			clean
				@ rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re