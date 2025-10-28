/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:34:18 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/28 17:10:35 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	try_to_eat(t_childs	*thread)
{
	int	idx;

	idx = thread->id;
	pthread_mutex_lock(&thread->main->forks[idx]);
	ft_putlog(thread, idx, 0);
	if (idx == *thread->main->arguments - 1)
		pthread_mutex_lock(&thread->main->forks[0]);
	else
		pthread_mutex_lock(&thread->main->forks[idx + 1]);
	if (idx == *thread->main->arguments - 1)
		ft_putlog(thread, 0, 0);
	else
		ft_putlog(thread, idx + 1, 0);
	ft_putlog(thread, idx, 1);
	usleep(thread->main->arguments[2] * 1000);
	pthread_mutex_unlock(&thread->main->forks[idx]);
	if (idx == *thread->main->arguments - 1)
		pthread_mutex_unlock(&thread->main->forks[0]);
	else
		pthread_mutex_unlock(&thread->main->forks[idx + 1]);
	return (0);
}

void	wait_all_childs(t_philos *main)
{
	while (!get_bool(main, &main->dinner_ready))
		;
}

void	*routine(void *args)
{
	t_childs	*thread;

	thread = (t_childs *)args;
	wait_all_childs(thread->main);
	pthread_mutex_lock(&thread->main->eating);
	try_to_eat(thread);
	pthread_mutex_unlock(&thread->main->eating);
	ft_putlog(thread, thread->id, 2);
	return (NULL);
}
