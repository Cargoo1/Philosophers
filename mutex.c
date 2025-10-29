/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 22:33:48 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/29 22:55:47 by acamargo         ###   ########.fr       */
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
