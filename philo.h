/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:34:39 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/27 15:20:47 by acamargo         ###   ########.fr       */
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
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log;
	pthread_mutex_t	eating;
	struct timeval	reference;
	struct timeval	current;
}	t_philos;

typedef struct	s_childs
{
	int			id;
	t_philos	*main;
}	t_childs;

int	ft_atoi(char *string);

int get_current_time(t_philos *main);

#endif
