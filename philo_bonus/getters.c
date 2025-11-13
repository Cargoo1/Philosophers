/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:18:21 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/13 19:20:09 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

int	get_bool(sem_t *semaphore, int *value)
{
	int	res;

	sem_wait(semaphore);
	res = *value;
	sem_post(semaphore);
	return (res);
}

long	get_long(sem_t *semaphore, long *value)
{
	long	res;

	sem_wait(semaphore);
	res = *value;
	sem_post(semaphore);
	return (res);
}
