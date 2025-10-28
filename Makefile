SRCS = ft_atoi.c philo.c time.c setters.c getters.c dinner.c putlog.c
INCLUDES = philo.h
CFLAGS = -Wall -Wextra -Werror -g3 -lpthread
MAKE_FLAGS = --no-print-directory
OBJS = $(SRCS:.c=.o)
NAME = philo
RMOBJS = rm -f $(OBJS)
RMEXE = rm -f $(NAME)

all: $(NAME)

$(NAME): $(INCLUDES) $(OBJS)
	gcc $(OBJS) -o $(NAME) $(CFLAGS)

$(OBJS): %.o: %.c

%.o: %.c
	@gcc $(CFLAGS) -g -c $< -o $@ 

clean: $(OBJS)
	$(RMOBJS)

fclean: clean
	$(RMEXE)
