SRCS = main.c philos.c logs.c ft_atoi.c
OBJS = ${SRCS:%c=%o}
INCLUDES = philo_bonus.h
CFLAGS = -Werror -Wall -Wextra -g3 -lpthread
GCC = gcc
NAME = philo_bonus
RMOBJS = rm -f $(OBJS)
RMEXE = rm -f $(NAME)

all: $(NAME)

$(NAME): $(INCLUDES) $(OBJS)
	$(GCC) $(SRCS) $(CFLAGS) -o $(NAME)

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	$(RMOBJS)

fclean: clean
	$(RMEXE)

re: fclean all
