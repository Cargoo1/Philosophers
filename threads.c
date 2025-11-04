/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:07:09 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/04 20:11:51 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

int	init_childs(t_philos *main, t_forks *forks)
{
	int			i;
	t_childs	*childs;

	i = 0;
	childs = malloc(sizeof(t_childs) * main->n_philos);
	if (!childs)
		return (main->errno = ERMALLOC, ERMALLOC);
	while (i < main->n_philos)
	{
		(childs[i]).id = i + 1;
		assing_forks(main, forks, childs, i);
		if (init_mutex(&childs[i].mtx_philo))
			return (main->errno = ERMUTEX, ERMUTEX);
		(childs[i]).main = main;
		(childs[i]).ready = 0;
		(childs[i]).last_meal = 0;
		(childs[i]).meals = 0;
		i++;
	}
	main->childs = childs;
	return (0);
}

int	init_threads(t_philos *main)
{
	if (main->n_philos == 0)
		return (1);
	main->forks = malloc(sizeof(t_forks) * main->n_philos);
	if (!main->forks)
		return (main->errno = ERMALLOC, ERMALLOC);
	if (create_forks(main, main->forks, main->n_philos))
		return (1);
	if (init_childs(main, main->forks))
		return (1);
	if (init_mutex(&main->log)
	| init_mutex(&main->global)
	| init_mutex(&main->start_dinner))
		return (main->errno = ERMUTEX, ERMUTEX);
	if (main->n_philos == 1)
		main->t_t_think = main->t_t_die;
	else if (main->n_philos % 2 == 0 && main->t_t_eat > main->t_t_sleep)
		main->t_t_think = main->t_t_eat - main->t_t_sleep;
	else if (main->n_philos % 2)
		main->t_t_think = main->t_t_eat;
	else
		main->t_t_think = 0;
	return (0);
}

int	create_threads(t_philos *main)
{
	t_childs	monitor;
	int			i;

	i = 0;
	main->t_t_start = get_current_time(MILISEC) + (main->n_philos * 10);
	pthread_mutex_lock(&main->start_dinner);
	while (i < main->n_philos)
	{
		if (pthread_create(&(main->childs[i]).thread, NULL, routine, &main->childs[i]))
			return (main->errno = ERTHREAD, ERTHREAD);
		i++;
	}
	if (create_monitor(main, &monitor))
		return (1);
	pthread_mutex_unlock(&main->start_dinner);
	i = 0;
	while (i < main->n_philos)
	{
		if (pthread_join((main->childs[i]).thread, NULL))
			return (main->errno = ERTHREAD, ERTHREAD);
		i++;
	}
	destroy_mutex(main->forks, main->n_philos);
	free(main->forks);
	return (0);
}
