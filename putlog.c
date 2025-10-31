/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putlog.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:35:47 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/31 22:39:12 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putlog(t_childs *thread, int id, t_mode mode)
{
	long	time;

	time = get_current_time(MILISEC) - thread->main->reference;
	pthread_mutex_lock(&thread->main->log);
	(void)id;
	if (mode == PICKED)
		;
		//printf("%ld %d picked the fork %d\n", time, thread->id, id);
	else if (mode == EATING)
		printf("%ld %d is eating\n", time, thread->id);
	else if (mode == 6)
		printf("%ld %d finished eating\n", time, thread->id);
	else if (mode == SLEEPING)
		printf("%ld %d is sleeping\n", time, thread->id);
	else if (mode == THINKING)
		printf("%ld %d is thinking\n", time, thread->id);
	else if (mode == DIED)
		printf("%ld %d died\n", time, thread->id);
	pthread_mutex_unlock(&thread->main->log);
	return (0);
}
