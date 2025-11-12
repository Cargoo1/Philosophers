/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:52:03 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/12 20:20:21 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS

# define PHILO_BONUS

# include <fcntl.h>

# include <semaphore.h>

# include <stdio.h>

# include <unistd.h>

# include <stdlib.h>

# include <sys/wait.h>

# include <sys/time.h>

# define ERSEM 2

# define ERNOMEM 3

# define ERFORK 4

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

typedef struct s_child
{
	long			last_meal;
	int				meals;
	int				id;
	long			reference;
	struct s_philos	*main;
}	t_child;

typedef struct s_philos
{
	int			n_philos;
	long		t_t_start;
	int			t_t_die;
	int			t_t_eat;
	int			t_t_sleep;
	int			n_meals;
	const char	*sem_forks;
	const char	*sem_print_dead;
	const char	*sem_s_died;
	const char	*sem_putlog;
	sem_t		*someone_died;
	sem_t		*forks;
	sem_t		*putlog;
	sem_t		*print_dead;
	int			errno;
	t_child		*childs;
	int			*pids;
}	t_philos;


int		ft_putlog(t_child *philo, t_mode mode);

long	get_current_time();

int		ft_atoi(char *str);

int		create_philos(t_philos *main);

int		im_i_dead(t_child *philo);
#endif
