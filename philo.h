/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:34:39 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/04 17:51:05 by acamargo         ###   ########.fr       */
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

# define ERMUTEX 4

# define TIME long

typedef TIME sec;

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

typedef struct s_philos
{
	int				n_philos;
	int				t_t_eat;
	int				t_t_think;
	int				t_t_sleep;
	int				t_t_die;
	int				all_full;
	int				stop_dinner;
	int				someone_died;
	int				errno;
	pthread_mutex_t	log;
	pthread_mutex_t	global;
	pthread_mutex_t	start_dinner;
	struct s_childs	*childs;
	struct s_forks	*forks;
	long			t_t_start;
}	t_philos;

typedef struct s_forks
{
	int				id;
	pthread_mutex_t	fork;
}	t_forks;

typedef struct s_printer
{
	pthread_t	thread;
	t_philos	*main;
	int			id_thread;
	int			id_fork;
	t_mode		mode;
}	t_printer;


typedef struct	s_childs
{
	pthread_t		thread;
	pthread_mutex_t	mtx_philo;
	int				id;
	long			last_meal;
	int				meals;
	int				ready;
	t_philos		*main;
	t_forks			*firts_fork;
	t_printer		printer;
	pthread_t		thread_p;
	t_forks			*second_fork;
}	t_childs;



void test_sleep(t_philos *main, sec time);

// Setters and getteres

int		get_bool(pthread_mutex_t *mtx, int *boolean);

void	set_bool(pthread_mutex_t *mtx, int *boolean, int value);

int		get_int(pthread_mutex_t *mtx, int *num);

void	set_int(pthread_mutex_t *mtx, int *num, int value);

void	set_long(pthread_mutex_t *mtx, long *num, long value);

long	get_long(pthread_mutex_t *mtx, long *num);
//

// Mutex

int		init_mutex(pthread_mutex_t *mtx);

int		change_mtx(pthread_mutex_t *mtx, t_mode mode);

int		destroy_mutex(t_forks *forks, int n_forks);

//

// Precise usleep

void	ft_usleep(t_philos *main, sec microsec);

//

// Threads

int		init_childs(t_philos *main, t_forks *forks);

int		init_threads(t_philos *main);

int		create_threads(t_philos *main);

//

//	Forks

int		create_forks(t_philos *main, t_forks *forks, int n_forks);

int		assing_forks(t_philos *main, t_forks *forks, t_childs *childs, int i);

//

int		create_monitor(t_philos *main, t_childs *monitor);

void	wait_all_childs(t_philos *main);

int		ft_atoi(char *string);

char	*ft_ltoa(long n);

int		ft_putlog(t_childs *thread, int id, t_mode mode);

long	get_current_time(t_mode mode);

int		try_to_eat(t_childs	*thread, t_philos *main);

void	*routine(void *args);
#endif
