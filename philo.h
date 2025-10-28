/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:34:39 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/28 15:53:03 by acamargo         ###   ########.fr       */
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


typedef struct s_philos
{
	int				*arguments;
	int				dinner_ready;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log;
	pthread_mutex_t	setter;
	pthread_mutex_t	getter;
	pthread_mutex_t	eating;
	unsigned long	reference;
	struct timeval	current;
}	t_philos;

typedef struct	s_childs
{
	int			id;
	t_philos	*main;
}	t_childs;

typedef enum t_mode
{
	MILISEC,
	MICROSEC,
	SEC
}	t_mode;

// Setters and getteres

int		get_bool(t_philos *main, int *boolean);

void	set_bool(t_philos *main, int *boolean, int value);

//

int		ft_atoi(char *string);

int		ft_putlog(t_childs *thread, int id, int mode);

unsigned long	get_current_time(t_mode mode);

int		try_to_eat(t_childs	*thread);

void	*routine(void *args);
#endif
