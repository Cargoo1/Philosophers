/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:45:36 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/03 20:20:43 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mtx, int *boolean, int value)
{
	pthread_mutex_lock(mtx);
	*boolean = value;
	pthread_mutex_unlock(mtx);
}

void	set_int(pthread_mutex_t *mtx, int *num, int value)
{
	if (change_mtx(mtx, LOCK))
		return;
	*num = value;
	if (change_mtx(mtx, UNLOCK))
		return;
}

void	increment_int(pthread_mutex_t *mtx, int *num, int value)
{
	if (change_mtx(mtx, LOCK))
		return;
	*num += value;
	if (change_mtx(mtx, UNLOCK))
		return;
}

void	set_long(pthread_mutex_t *mtx, long *num, long value)
{
	pthread_mutex_lock(mtx);
	*num = value;
	pthread_mutex_unlock(mtx);
}
