/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:33:50 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/31 22:42:39 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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


int	destroy_mutex(t_forks *forks, int n_forks)
{
	int	i;

	i = 0;
	while (i < n_forks)
	{
		pthread_mutex_destroy(&forks[i].fork);
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

int	create_forks(t_forks *forks, int n_forks)
{
	int	i;

	i = 0;
	while (i < n_forks)
	{
		if (pthread_mutex_init(&forks[i].fork, NULL))
			return (1);
		forks[i].id = i;
		i++;
	}
	return (0);
}

t_childs	*init_childs(t_philos *main, t_forks *forks, pthread_t *threads)
{
	int			i;
	t_childs	*childs;

	i = 0;
	childs = malloc(sizeof(t_childs) * main->arguments[0]);
	if (!childs)
		return (NULL);
	while (i < main->arguments[0])
	{
		(childs[i]).id = i + 1;
		if ((childs[i]).id % 2 == 0)
		{
			(childs[i]).firts_fork = &forks[i];
			(childs[i]).second_fork = &forks[(i + 1) % *main->arguments];
		}
		else
		{
			(childs[i]).firts_fork = &forks[(i + 1) % *main->arguments];
			(childs[i]).second_fork = &forks[i];
		}
		(childs[i]).thread = &threads[i];
		(childs[i]).main = main;
		(childs[i]).last_meal = 0;
		(childs[i]).meals = 0;
		i++;
	}
	return (childs);
}

int	init_threads(t_philos *main)
{
	int				i;
	pthread_t		*threads;
	t_childs		monitor;

	i = 0;
	threads = malloc(sizeof(pthread_t) * *main->arguments);
	if (!threads)
		return (ERMALLOC);
	monitor.thread = malloc(sizeof(pthread_t));
	if (!monitor.thread)
		return (ERMALLOC);
	main->forks = malloc(sizeof(t_forks) * *main->arguments);
	if (!main->forks)
		return (ERMALLOC);
	if (create_forks(main->forks, main->arguments[0]))
		return (1);
	main->childs = init_childs(main, main->forks, threads);
	init_mutex(&main->log);
	init_mutex(&main->global);
	init_mutex(&main->eating);
	//if (create_monitor(main, &monitor))
		//return (1);
	while (i < *main->arguments)
	{
		if (pthread_create((main->childs[i]).thread, NULL, routine, &main->childs[i]))
			return (ERTHREAD);
		i++;
	}
	set_long(main, &main->reference, get_current_time(MILISEC));
	set_bool(main, &main->dinner_ready, 1);
	i = 0;
	while (i < *main->arguments)
	{
		pthread_join(*(main->childs[i]).thread, NULL);
		i++;
	}
	free(threads);
	destroy_mutex(main->forks, *main->arguments);
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
	main.all_full = 0;
	main.someone_died = 0;
	main.dinner_ready = 0;
	main.stop_dinner = 0;
	if (!main.arguments)
		return (FAILURE);
	init_threads(&main);
}
