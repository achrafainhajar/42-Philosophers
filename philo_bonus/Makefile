SRC_BONUS = philo_bonus.c utils.c init.c utils2.c\

OBJ_BONUS = $(SRC_BONUS:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc
NAME_BONUS = philo_bonus

all : $(NAME_BONUS)
	
$(NAME_BONUS) : $(OBJ_BONUS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ_BONUS)
fclean :clean
	rm -rf $(NAME_BONUS)
re : clean all