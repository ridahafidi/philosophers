NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c \
	check_args.c \
	clean.c \
	dinner.c \
	dinner_utils.c \
	ft_usleep.c \
	philo_utils.c \
	routine.c \
	safe_malloc.c \
	safe_mutex.c \
	safe_thread.c \
	state_print.c \
	str_utils.c \
	time.c \
	extra_utils.c

OBJS = $(SRCS:.c=.o)

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
