/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:09:48 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/31 22:38:44 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	*monitoring_philos(void *args)
{
	int			i;
	t_childs	*monitor;
	t_childs	*philos;
	long			time;
	t_philos	*main;

	monitor = (t_childs *)args;
	main = monitor->main;
	philos = main->childs;
	wait_all_childs(main);
	while (!get_bool(main, &main->stop_dinner))
	{
		i = 0;
		while (i < main->arguments[0])
		{
			time = get_current_time(MILISEC) - get_long(main, &philos[i].last_meal);
			printf("%ld\n\n", get_long(main, &philos[i].last_meal));
			if (time > main->arguments[1])
			{
				ft_putlog(&philos[i], i, DIED);
				set_bool(main, &main->stop_dinner, 1);
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
	if (pthread_create(monitor->thread, NULL, monitoring_philos, monitor))
		return (1);
	if (pthread_detach(*monitor->thread))
		return (1);
	return (0);
}
