/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:34:39 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/23 11:47:41 by acamargo         ###   ########.fr       */
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

typedef struct t_philos
{
	int				*arguments;
	pthread_t		*threads;
	struct timeval	reference;
}	s_philos;

int	ft_atoi(char *string);

#endif
