/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:33:50 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/27 15:24:08 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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

int	ft_putlog(t_childs *thread, int id, int mode)
{
	pthread_mutex_lock(&thread->main->log);
	if (mode == 0)
		printf("(%d) %d picked the fork %d\n", get_current_time(thread->main), thread->id, id);
	else if (mode == 1)
		printf("(%d) %d is eating\n", get_current_time(thread->main), thread->id);
	else if (mode == 2)
		printf("(%d) %d finished eating\n", get_current_time(thread->main), thread->id);
	pthread_mutex_unlock(&thread->main->log);
	return (0);
}

int	try_to_eat(t_childs	*thread)
{
	int	idx;

	idx = thread->id;
	pthread_mutex_lock(&thread->main->forks[idx]);
	ft_putlog(thread, idx, 0);
	if (idx == *thread->main->arguments - 1)
		pthread_mutex_lock(&thread->main->forks[0]);
	else
		pthread_mutex_lock(&thread->main->forks[idx + 1]);
	if (idx == *thread->main->arguments - 1)
		ft_putlog(thread, 0, 0);
	else
		ft_putlog(thread, idx + 1, 0);
	ft_putlog(thread, idx, 1);
	usleep(thread->main->arguments[2] * 1000);
	pthread_mutex_unlock(&thread->main->forks[idx]);
	if (idx == *thread->main->arguments - 1)
		pthread_mutex_unlock(&thread->main->forks[0]);
	else
		pthread_mutex_unlock(&thread->main->forks[idx + 1]);
	return (0);
}

void	*routine(void *args)
{
	t_childs	*thread;

	thread = (t_childs *)args;
	pthread_mutex_lock(&thread->main->eating);
	try_to_eat(thread);
	pthread_mutex_unlock(&thread->main->eating);
	ft_putlog(thread, thread->id, 2);
	return (NULL);
}

int	destroy_mutex(t_philos *main, int n_forks)
{
	int	i;

	i = 0;
	while (i < n_forks)
	{
		pthread_mutex_destroy(&main->forks[i]);
		i++;
	}
	return (0);
}

int	init_mutex(t_philos *main, int n_forks)
{
	int	i;

	i = 0;
	while (i < n_forks)
	{
		pthread_mutex_init(&main->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&main->log, NULL);
	pthread_mutex_init(&main->eating, NULL);
	return (0);
}

t_childs	*init_childs(t_philos *main)
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
		(childs[i]).main = main;
		i++;
	}
	return (childs);
}

int	init_threads(t_philos *main)
{
	int			i;
	t_childs	*childs;

	i = 0;
	main->threads = malloc(sizeof(pthread_t) * *main->arguments);
	if (!main->threads)
		return (ERMALLOC);
	main->forks = malloc(sizeof(pthread_mutex_t) * *main->arguments);
	if (!main->forks)
		return (ERMALLOC);
	init_mutex(main, main->arguments[0]);
	childs = init_childs(main);
	if (gettimeofday(&main->reference, NULL))
		return (1);
	while (i < *main->arguments)
	{
		if (pthread_create(&main->threads[i], NULL, routine, &childs[i]))
			return (ERTHREAD);
		i++;
	}
	i = 0;
	while (i < *main->arguments)
	{
		pthread_join(main->threads[i], NULL);
		i++;
	}
	free(main->threads);
	destroy_mutex(main, *main->arguments);
	free(main->forks);
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
	if (!main.arguments)
		return (FAILURE);
	init_threads(&main);
}
