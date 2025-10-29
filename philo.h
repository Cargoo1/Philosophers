/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:34:39 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/29 22:34:24 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

#define PHILO_H

# include <pthread.h>

# include <stdlib.h>

# include <stdio.h>

# include <sys/time.h>

# include <unistd.h>

# define ERMALLOC 2

# define FAILURE 1

# define ERTHREAD 3

# define TIME long

typedef TIME sec;

typedef struct s_philos
{
	int				*arguments;
	int				dinner_ready;
	int				stop_dinner;
	int				thread_turn;
	pthread_mutex_t	log;
	pthread_mutex_t	global;
	pthread_mutex_t	eating;
	unsigned long	reference;
	struct timeval	current;
}	t_philos;

typedef struct	s_childs
{
	pthread_t		*thread;
	int				id;
	t_philos		*main;
	pthread_mutex_t	*firts_fork;
	pthread_mutex_t	*second_fork;
}	t_childs;

typedef enum t_mode
{
	MILISEC,
	MICROSEC,
	SEC,
	UNLOCK,
	LOCK
}	t_mode;

// Setters and getteres

int		get_bool(t_philos *main, int *boolean);

void	set_bool(t_philos *main, int *boolean, int value);

int		get_int(t_philos *main, int *num);

void	set_int(t_philos *main, int *num, int value);
//

// Mutex

int		change_mtx(pthread_mutex_t *mtx, t_mode mode);

// Precise usleep
void	ft_usleep(t_philos *main, sec microsec);
//

int		ft_atoi(char *string);

int		ft_putlog(t_childs *thread, int id, int mode);

long	get_current_time(t_mode mode);

int		try_to_eat(t_childs	*thread, t_philos *main);

void	*routine(void *args);
#endif
