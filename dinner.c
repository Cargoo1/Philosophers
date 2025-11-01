/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:34:18 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/01 17:33:11 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	try_to_eat(t_childs	*thread, t_philos *main)
{
	change_mtx(&thread->firts_fork->fork, LOCK);
	ft_putlog(thread, thread->firts_fork->id, PICKED);
	change_mtx(&thread->second_fork->fork, LOCK);
	ft_putlog(thread, thread->second_fork->id, PICKED);
	set_long(&thread->mtx_philo, &thread->last_meal, get_current_time(MILISEC));
	ft_putlog(thread, thread->last_meal, EATING);
	ft_usleep(main, main->arguments[2] * 1000);
	change_mtx(&thread->firts_fork->fork, UNLOCK);
	change_mtx(&thread->second_fork->fork, UNLOCK);
	return (0);
}

void	wait_all_childs(t_philos *main)
{
	while (!get_bool(&main->global, &main->dinner_ready))
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
		if (get_bool(&main->global, &main->stop_dinner))
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

int	sleeping(t_childs *thread, t_philos *main)
{
	if (ft_putlog(thread, thread->id, SLEEPING))
		return (1);
	ft_usleep(main, main->arguments[3] *1000);
	return (0);
}


int	thinking(t_childs *thread, t_philos *main)
{
	sec	time_to_think;

	if (thread->id % 2 != 0)
		return (0);
	time_to_think = main->arguments[1] - main->arguments[2] + main->arguments[3];
	if (time_to_think <= 0)
		time_to_think = 0;
	ft_putlog(thread, thread->id, THINKING);
	ft_usleep(main, time_to_think * 1000);
	return (0);
}

void	*routine(void *args)
{
	t_childs	*thread;
	t_philos	*main;

	thread = (t_childs *)args;
	main = thread->main;
	/* TODO
	if (*main->arguments == 1)
		one_philo()
	*/
	wait_all_childs(thread->main);
	set_long(&thread->mtx_philo, &thread->last_meal, get_current_time(MILISEC));
	set_bool(&thread->mtx_philo, &thread->ready, 1);
	if (thread->id % 2 == 0)
		ft_usleep(main, main->arguments[2] * 1000);
	while (!get_bool(&main->global, &main->stop_dinner))
	{
		try_to_eat(thread, main);
		sleeping(thread, main);
		//thinking(thread, main);
	}
	return (NULL);
}
