/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:09:48 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/10 20:08:35 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			break ;
		usleep(100);
	}
}

int	everyone_is_full(t_childs *philos, t_philos *main)
{
	int	philos_full;
	int	i;

	i = 0;
	philos_full = 0;
	while (i < main->n_philos)
	{
		if (get_bool(&(philos[i]).mtx_philo, &(philos[i]).full))
			philos_full++;
		i++;
	}
	if (philos_full == main->n_philos)
		return (1);
	return (0);
}

int	is_someone_dead(t_childs *philos, t_philos *main, int i)
{
	t_sec	time;

	time = get_current_time(MILISEC)
		- get_long(&(philos[i]).mtx_philo, &(philos[i]).last_meal);
	if ((time > main->t_t_die)
		&& !get_bool(&(philos[i].mtx_philo), &(philos[i]).full))
	{
		set_bool(&main->global, &main->stop_dinner, 1);
		ft_putlog(&main->childs[i], i, DIED);
		return (1);
	}
	return (0);
}

void	*monitoring_philos(void *args)
{
	int			i;
	t_childs	*philos;
	t_philos	*main;
	t_childs	*monitor;

	monitor = (t_childs *)args;
	main = monitor->main;
	philos = main->childs;
	wait_to_dinner(main);
	i = 0;
	while (!everyone_is_full(philos, main))
	{
		i = 0;
		while (i < main->n_philos)
		{
			if (is_someone_dead(philos, main, i))
				return (NULL);
			i++;
		}
		usleep(100);
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
	return (0);
}
