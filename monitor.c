/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:09:48 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/01 16:01:25 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

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
		while (i < main->arguments[0])
		{
			if (get_bool(&(philos[i]).mtx_philo, &(philos[i]).ready))
				all_ready++;
			i++;
		}
		if (all_ready == main->arguments[0])
			break;
	}
}

void	*monitoring_philos(void *args)
{
	int			i;
	long		time;
	t_childs	*philos;
	t_philos	*main;

	main = (t_philos *)args;
	philos = main->childs;
	wait_to_dinner(main);
	i = 0;
	while (!get_bool(&main->global, &main->stop_dinner))
	{
		i = 0;
		while (i < main->arguments[0])
		{
			time = get_current_time(MILISEC) - get_long(&(philos[i]).mtx_philo, &(philos[i]).last_meal);
			if (time > main->arguments[1])
			{
				ft_putlog(&main->childs[i], i, DIED);
				set_bool(&main->global, &main->stop_dinner, 1);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}

int	create_monitor(t_philos *main, t_childs *monitor)
{
	monitor->id = 0;
	monitor->main = main;
	monitor->firts_fork = NULL;
	monitor->second_fork = NULL;
	monitor->thread = malloc(sizeof(pthread_t));
	if (pthread_create(monitor->thread, NULL, monitoring_philos, main))
		return (1);
	if (pthread_detach(*monitor->thread))
		return (1);
	return (0);
}
