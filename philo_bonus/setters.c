/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:20:16 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/13 19:23:39 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

void	set_bool(sem_t *semaphore, int *variable, int value)
{
	sem_wait(semaphore);
	*variable = value;
	sem_post(semaphore);
}

void	increment_int(sem_t *semaphore, int *variable, int value)
{
	sem_wait(semaphore);
	*variable += value;
	sem_post(semaphore);
}

void	set_long(sem_t *semaphore, long *variable, long value)
{
	sem_wait(semaphore);
	*variable = value;
	sem_post(semaphore);
}
