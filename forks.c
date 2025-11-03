/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:09:23 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/03 21:10:12 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_philos *main, t_forks *forks, int n_forks)
{
	int	i;

	i = 0;
	while (i < n_forks)
	{
		if (pthread_mutex_init(&forks[i].fork, NULL))
			return (main->errno = ERMUTEX, ERMUTEX);
		forks[i].id = i;
		i++;
	}
	return (0);
}

int	assing_forks(t_philos *main, t_forks *forks, t_childs *childs, int i)
{
	if ((childs[i]).id % 2 == 0)
	{
		(childs[i]).firts_fork = &forks[i];
		(childs[i]).second_fork = &forks[(i + 1) % main->n_philos];
	}
	else
	{
		(childs[i]).firts_fork = &forks[(i + 1) % main->n_philos];
		(childs[i]).second_fork = &forks[i];
	}
	return (0);
}
