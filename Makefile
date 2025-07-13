CFLAGS = #`-pthread #-fsanitize=thread -g3

SRC = 	clear.c\
		debug.c\
		ft_atoi.c\
		ft_usleep.c\
		init_table.c\
		log.c\
		lunch_threads.c\
		parse.c\
		philo_brain.c\
		philosopher.c\
		the_observer.c\
		utils.c

OBJ =	$(SRC:.c=.o)

NAME= philo

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ)  -o $(NAME)

%.o: %.c philo.h
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
