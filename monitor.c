/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:09:48 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/04 18:43:44 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	wait_to_dinner(t_philos *main)
{
	t_childs	*philos;
	int			all_ready;
	int			i;

	philos = main->childs;
	all_ready = 0;
	while (1)
	{
		i = 0;
		all_ready = 0;
		while (i < main->n_philos)
		{
			if (get_bool(&(philos[i]).mtx_philo, &(philos[i]).ready))
				all_ready++;
			i++;
		}
		if (all_ready == main->n_philos)
			break;
		usleep(500);
	}
}

void	*monitoring_philos(void *args)
{
	int			i;
	long		time;
	t_childs	*philos;
	t_philos	*main;
	t_childs	*monitor;


	monitor = (t_childs *)args;
	main = monitor->main;
	philos = main->childs;
	//change_mtx(&monitor->mtx_philo, LOCK);
	//change_mtx(&monitor->mtx_philo, UNLOCK);
	wait_to_dinner(main);
	//wait_all_childs(main);
	i = 0;
	while (1)
	{
		i = 0;
		while (i < main->n_philos)
		{
			time = get_current_time(MILISEC) - get_long(&(philos[i]).mtx_philo, &(philos[i]).last_meal);
			if (time > main->t_t_die)
			{
				ft_putlog(&main->childs[i], i, DIED);
				set_bool(&main->global, &main->stop_dinner, 1);
				return (NULL);
			}
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

int	create_monitor(t_philos *main, t_childs *monitor)
{
	monitor->id = -1;
	monitor->main = main;
	monitor->firts_fork = NULL;
	monitor->second_fork = NULL;
	if (pthread_create(&monitor->thread, NULL, monitoring_philos, monitor))
		return (main->errno = ERTHREAD, ERTHREAD);
	if (pthread_detach(monitor->thread))
		return (main->errno = ERTHREAD, ERTHREAD);
	return (0);
}
