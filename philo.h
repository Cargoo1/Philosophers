/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:34:39 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/01 15:51:55 by acamargo         ###   ########.fr       */
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
	int				all_full;
	int				stop_dinner;
	int				someone_died;
	int				thread_turn;
	pthread_mutex_t	log;
	pthread_mutex_t	global;
	pthread_mutex_t	eating;
	struct s_childs	*childs;
	struct s_forks	*forks;
	long			reference;
	struct timeval	current;
}	t_philos;

typedef struct s_forks
{
	int				id;
	pthread_mutex_t	fork;
}	t_forks;

typedef struct	s_childs
{
	pthread_t		*thread;
	pthread_mutex_t	mtx_philo;
	int				id;
	long			last_meal;
	int				meals;
	int				ready;
	t_philos		*main;
	t_forks			*firts_fork;
	t_forks			*second_fork;
}	t_childs;

typedef enum t_mode
{
	MILISEC,
	MICROSEC,
	SEC,
	UNLOCK,
	LOCK,
	EATING,
	PICKED,
	SLEEPING,
	THINKING,
	DIED
}	t_mode;

// Setters and getteres

int		get_bool(pthread_mutex_t *mtx, int *boolean);

void	set_bool(pthread_mutex_t *mtx, int *boolean, int value);

int		get_int(pthread_mutex_t *mtx, int *num);

void	set_int(pthread_mutex_t *mtx, int *num, int value);

void	set_long(pthread_mutex_t *mtx, long *num, long value);

long	get_long(pthread_mutex_t *mtx, long *num);
//

// Mutex

int		change_mtx(pthread_mutex_t *mtx, t_mode mode);

// Precise usleep
void	ft_usleep(t_philos *main, sec microsec);
//

int		create_monitor(t_philos *main, t_childs *monitor);

void	wait_all_childs(t_philos *main);

int		ft_atoi(char *string);

int		ft_putlog(t_childs *thread, int id, t_mode mode);

long	get_current_time(t_mode mode);

int		try_to_eat(t_childs	*thread, t_philos *main);

void	*routine(void *args);
#endif
