/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:07:09 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/03 21:21:26 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	main->forks = malloc(sizeof(t_forks) * main->n_philos);
	if (!main->forks)
		return (main->errno = ERMALLOC, ERMALLOC);
	if (create_forks(main, main->forks, main->n_philos))
		return (1);
	if (init_childs(main, main->forks))
		return (1);
	if (init_mutex(&main->log)
	| init_mutex(&main->global))
		return (main->errno = ERMUTEX, ERMUTEX);
	return (0);
}

int	create_threads(t_philos *main)
{
	t_childs	monitor;
	int			i;

	i = 0;
	main->t_t_start = get_current_time(MILISEC) + (main->n_philos * 10);
	if (create_monitor(main, &monitor))
		return (1);
	while (i < main->n_philos)
	{
		if (pthread_create(&(main->childs[i]).thread, NULL, routine, &main->childs[i]))
			return (main->errno = ERTHREAD, ERTHREAD);
		i++;
	}
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
