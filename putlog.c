/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putlog.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:35:47 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/28 16:05:04 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putlog(t_childs *thread, int id, int mode)
{
	unsigned long	time;

	time = get_current_time(MILISEC) - thread->main->reference;
	pthread_mutex_lock(&thread->main->log);
	if (mode == 0)
		printf("(%lu) %d picked the fork %d\n", time, thread->id, id);
	else if (mode == 1)
		printf("(%lu) %d is eating\n", time, thread->id);
	else if (mode == 2)
		printf("(%lu) %d finished eating\n", time, thread->id);
	pthread_mutex_unlock(&thread->main->log);
	return (0);
}
