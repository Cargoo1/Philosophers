/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:34:18 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/05 19:55:44 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

void test_sleep(t_philos *main, sec time)
{
	sec	goal_t;

	goal_t = get_current_time(MILISEC) + time;
	while (get_current_time(MILISEC) < goal_t && !get_bool(&main->global, &main->stop_dinner))
		usleep(100);
}

int	try_to_eat(t_childs	*thread, t_philos *main)
{
	pthread_mutex_lock(&thread->firts_fork->fork);
	ft_putlog(thread, thread->firts_fork->id, PICKED);
	pthread_mutex_lock(&thread->second_fork->fork);
	ft_putlog(thread, thread->second_fork->id, PICKED);
	/*
	change_mtx(&thread->firts_fork->fork, LOCK);
	//ft_putlog(thread, thread->firts_fork->id, PICKED);
	change_mtx(&thread->second_fork->fork, LOCK);
	//ft_putlog(thread, thread->second_fork->id, PICKED);
	*/
	if (get_bool(&main->global, &main->stop_dinner))
	{
		pthread_mutex_unlock(&thread->second_fork->fork);
		pthread_mutex_unlock(&thread->firts_fork->fork);
		return (1);
	}
	set_long(&thread->mtx_philo, &thread->last_meal, get_current_time(MILISEC));
	ft_putlog(thread, thread->last_meal, EATING);
	test_sleep(main, main->t_t_eat);
	//ft_usleep(main, main->t_t_eat * 1000);
	pthread_mutex_unlock(&thread->second_fork->fork);
	pthread_mutex_unlock(&thread->firts_fork->fork);
	ft_putlog(thread, 1, SLEEPING);
	test_sleep(main, main->t_t_sleep);
	/*
	change_mtx(&thread->firts_fork->fork, UNLOCK);
	change_mtx(&thread->second_fork->fork, UNLOCK);
	*/
	return (0);
}

void	wait_all_childs(t_philos *main)
{
	while (get_current_time(MILISEC) < main->t_t_start)
		usleep(100);
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
	if (get_bool(&main->global, &main->stop_dinner))
		return (0);
	ft_putlog(thread, thread->id, SLEEPING);
	test_sleep(main, main->t_t_sleep);
	return (0);
}


int	thinking(t_childs *thread, t_philos *main, int silent_mode)
{
	//sec	time_to_think;

	if (silent_mode)
		test_sleep(main, main->t_t_eat);
	else
	{
		ft_putlog(thread, thread->id, THINKING);
		test_sleep(main, main->t_t_think);
		//test_sleep(main, main->t_t_think);
		return (0);
	}
	return (0);
}

void	*routine(void *args)
{
	t_childs	*thread;
	t_philos	*main;

	thread = (t_childs *)args;
	main = thread->main;
	set_long(&thread->mtx_philo, &thread->last_meal, main->t_t_start);
	set_bool(&thread->mtx_philo, &thread->ready, 1);
	wait_all_childs(thread->main);
	if (main->n_philos == 1)
	{
		test_sleep(main, main->t_t_die + 100);
		return (NULL);
	}
	if (thread->id % 2 == 0)
		test_sleep(main, main->t_t_eat);
	while (!get_bool(&main->global, &main->stop_dinner))
	{
		if (try_to_eat(thread, main))
			break ;
		/*
		if (get_bool(&main->global, &main->stop_dinner))
			break ;
		*/
		thinking(thread, main, 0);
	}
	return (NULL);
}
