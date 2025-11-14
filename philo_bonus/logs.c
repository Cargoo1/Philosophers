/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:25:21 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/14 14:10:54 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

int	ft_putlog(t_child *philo, t_mode mode)
{
	long	time;

	sem_wait(philo->main->putlog);
	if (get_bool(philo->local, &philo->im_dead) && mode != DIED)
	{
		sem_post(philo->main->putlog);
		return (1);
	}
	time = get_current_time() - philo->main->t_t_start;
	if (mode == PICKED)
		printf("%ld %d has taken fork\n", time, philo->id);
	else if (mode == EATING)
		printf("%ld %d is eating\n", time, philo->id);
	else if (mode == SLEEPING)
		printf("%ld %d is sleeping\n", time, philo->id);
	else if (mode == THINKING)
		printf("%ld %d is thinking\n", time, philo->id);
	else if (mode == DIED)
	{
		printf("%ld %d died\n", time, philo->id);
		return (0);
	}
	sem_post(philo->main->putlog);
	return (0);
}
