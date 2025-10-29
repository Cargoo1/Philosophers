/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:34:18 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/29 22:59:53 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int	try_to_eat(t_childs	*thread, t_philos *main)
{
	change_mtx(thread->firts_fork, LOCK);
	ft_putlog(thread, thread->id, 0);
	change_mtx(thread->second_fork, LOCK);
	ft_putlog(thread, thread->id, 0);
	ft_putlog(thread, thread->id, 1);
	ft_usleep(main, main->arguments[2] * 1000);
	change_mtx(thread->firts_fork, UNLOCK);
	change_mtx(thread->second_fork, UNLOCK);
	return (0);
}

void	wait_all_childs(t_philos *main)
{
	while (!get_bool(main, &main->dinner_ready))
		;
}

void	ft_usleep(t_philos *main, sec microsec)
{
	sec	start;
	sec	elapsed;
	sec	rem;

	start = get_current_time(MICROSEC);
	while (get_current_time(MICROSEC) - start < microsec)
	{
		if (get_bool(main, &main->stop_dinner))
			break;
		elapsed = get_current_time(MICROSEC) - start;
		rem = microsec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
		{
			while (get_current_time(MICROSEC) - start < microsec)
				;
		}
	}
}

void	*routine(void *args)
{
	t_childs	*thread;
	t_philos	*main;

	thread = (t_childs *)args;
	main = thread->main;
	wait_all_childs(thread->main);
	while (!get_bool(main, &main->stop_dinner))
	{
		try_to_eat(thread, main);
		ft_usleep(main, main->arguments[3]* 1000);
	}
	return (NULL);
}
