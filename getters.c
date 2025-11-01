/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:41:23 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/01 15:07:57 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>

int	get_bool(pthread_mutex_t *mtx, int *boolean)
{
	int	res;

	change_mtx(mtx, LOCK);
	res = *boolean;
	change_mtx(mtx, UNLOCK);
	return (res);
}

int	get_int(pthread_mutex_t *mtx, int *num)
{
	int	res;
	if (change_mtx(mtx, LOCK))
		return (1);
	res = *num;
	if (change_mtx(mtx, UNLOCK))
		return (1);
	return (res);
}

long	get_long(pthread_mutex_t *mtx, long *num)
{
	long	res;
	
	if (change_mtx(mtx, LOCK))
		return (1);
	res = *num;
	if (change_mtx(mtx, UNLOCK))
		return (1);
	return (res);
}
