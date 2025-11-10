SRCS = ft_atoi.c philo.c time.c setters.c getters.c dinner.c putlog.c mutex.c monitor.c ft_ltoa.c \
	   forks.c threads.c
INCLUDES = philo.h
CFLAGS = -Wall -Wextra -Werror -g3
MAKE_FLAGS = --no-print-directory
OBJS = ${SRCS:%c=%o}
NAME = philo
RMOBJS = rm -f $(OBJS)
RMEXE = rm -f $(NAME)

all: $(NAME)

$(NAME): $(INCLUDES) $(OBJS)
	cc $(OBJS) -o $(NAME) $(CFLAGS)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ 

clean:
	$(RMOBJS)

fclean: clean
	$(RMEXE)

re: fclean all
