/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putlog.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:35:47 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/10 17:46:12 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putlog(t_childs *thread, int id, t_mode mode)
{
	long	time;

	pthread_mutex_lock(&thread->main->log);
	if (get_bool(&thread->main->global, &thread->main->stop_dinner)
		&& mode != DIED)
	{
		pthread_mutex_unlock(&thread->main->log);
		return (1);
	}
	(void)id;
	time = get_current_time(MILISEC) - thread->main->t_t_start;
	if (mode == PICKED)
		printf("%ld %d has taken fork\n", time, thread->id);
	else if (mode == EATING)
		printf("%ld %d is eating\n", time, thread->id);
	else if (mode == SLEEPING)
		printf("%ld %d is sleeping\n", time, thread->id);
	else if (mode == THINKING)
		printf("%ld %d is thinking\n", time, thread->id);
	else if (mode == DIED)
		printf("%ld %d died\n", time, thread->id);
	pthread_mutex_unlock(&thread->main->log);
	return (0);
}
