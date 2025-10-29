/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:33:50 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/29 22:49:45 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	double_pointer_len(char **s)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (s[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	*verify_arguments(char **argv)
{
	int	i;
	int	j;
	int	*args_lst;
	int	args_count;

	i = 1;
	args_count = double_pointer_len(argv);
	while (argv[i])
	{
		if (!ft_atoi(argv[i]) && argv[i][0] != '0')
			return (NULL);
		i++;
	}
	i = 1;
	j = 0;
	args_lst = malloc(sizeof(int) * args_count);
	if (!args_lst)
		return (NULL);
	while (argv[i])
	{
		args_lst[j] = ft_atoi(argv[i]);
		j++;
		i++;
	}
	return (args_lst);
}


int	destroy_mutex(pthread_mutex_t *forks, int n_forks)
{
	int	i;

	i = 0;
	while (i < n_forks)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	return (0);
}

int	init_mutex(pthread_mutex_t *mtx)
{
	if (pthread_mutex_init(mtx, NULL))
		return (1);
	return (0);
}

int	create_forks(pthread_mutex_t *forks, int n_forks)
{
	int	i;

	i = 0;
	while (i < n_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

t_childs	*init_childs(t_philos *main, pthread_mutex_t *forks, pthread_t *threads)
{
	int			i;
	t_childs	*childs;

	i = 0;
	childs = malloc(sizeof(t_childs) * main->arguments[0]);
	if (!childs)
		return (NULL);
	while (i < main->arguments[0])
	{
		(childs[i]).id = i;
		if ((childs[i]).id % 2 == 0)
		{
			(childs[i]).firts_fork = &forks[(i + 1) % *main->arguments];
			(childs[i]).second_fork = &forks[i];
		}
		else
		{
			(childs[i]).firts_fork = &forks[i];
			(childs[i]).second_fork = &forks[(i + 1) % *main->arguments];
		}
		(childs[i]).thread = &threads[i];
		(childs[i]).main = main;
		i++;
	}
	return (childs);
}

int	init_threads(t_philos *main)
{
	int				i;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	t_childs		*childs;

	i = 0;
	threads = malloc(sizeof(pthread_t) * *main->arguments);
	if (!threads)
		return (ERMALLOC);
	forks = malloc(sizeof(pthread_mutex_t) * *main->arguments);
	if (!forks)
		return (ERMALLOC);
	if (create_forks(forks, main->arguments[0]))
		return (1);
	childs = init_childs(main, forks, threads);
	init_mutex(&main->log);
	init_mutex(&main->global);
	init_mutex(&main->eating);
	while (i < *main->arguments)
	{
		if (pthread_create((childs[i]).thread, NULL, routine, &childs[i]))
			return (ERTHREAD);
		i++;
	}
	main->reference = get_current_time(MILISEC);
	set_bool(main, &main->dinner_ready, 1);
	i = 0;
	while (i < *main->arguments)
	{
		pthread_join(*(childs[i]).thread, NULL);
		i++;
	}
	free(threads);
	destroy_mutex(forks, *main->arguments);
	free(forks);
	free(main->arguments);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philos		main;

	if (argc > 6 || argc < 5)
	{
		printf("Incorrect number of arguments");
		return (1);
	}
	main.arguments = verify_arguments(argv);
	main.stop_dinner = 0;
	main.dinner_ready = 0;
	main.thread_turn = 0;
	if (!main.arguments)
		return (FAILURE);
	init_threads(&main);
}
