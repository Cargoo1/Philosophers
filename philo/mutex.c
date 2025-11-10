/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 22:33:48 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/03 21:08:54 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	change_mtx(pthread_mutex_t *mtx, t_mode mode)
{
	if (mode == LOCK)
	{
		if (pthread_mutex_lock(mtx))
			return (1);
	}
	else if (mode == UNLOCK)
	{
		if (pthread_mutex_unlock(mtx))
			return (1);
	}
	return (0);
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
		return (ERMUTEX);
	return (0);
}
