
SRC = philo.c utils.c init.c utils2.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc
NAME = philo
all : $(NAME)
	
$(NAME) : $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
	

clean :
	rm -rf $(OBJ)
fclean :clean
	rm -rf $(NAME)
re : clean all