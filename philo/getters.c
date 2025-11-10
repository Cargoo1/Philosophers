/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:41:23 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/10 17:46:55 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

int	get_bool(pthread_mutex_t *mtx, int *boolean)
{
	int	res;

	pthread_mutex_lock(mtx);
	res = *boolean;
	pthread_mutex_unlock(mtx);
	return (res);
}

int	get_int(pthread_mutex_t *mtx, int *num)
{
	int	res;

	pthread_mutex_lock(mtx);
	res = *num;
	pthread_mutex_unlock(mtx);
	return (res);
}

long	get_long(pthread_mutex_t *mtx, long *num)
{
	long	res;

	pthread_mutex_lock(mtx);
	res = *num;
	pthread_mutex_unlock(mtx);
	return (res);
}
