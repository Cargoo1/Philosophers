/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:34:18 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/10 20:08:05 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

void	ft_usleep(t_philos *main, t_sec time)
{
	t_sec	goal_t;

	goal_t = get_current_time(MILISEC) + time;
	while (get_current_time(MILISEC) < goal_t
		&& !get_bool(&main->global, &main->stop_dinner))
		usleep(100);
}

int	try_to_eat(t_childs	*thread, t_philos *main)
{
	pthread_mutex_lock(&thread->firts_fork->fork);
	ft_putlog(thread, thread->firts_fork->id, PICKED);
	pthread_mutex_lock(&thread->second_fork->fork);
	ft_putlog(thread, thread->second_fork->id, PICKED);
	if (get_bool(&main->global, &main->stop_dinner))
	{
		pthread_mutex_unlock(&thread->second_fork->fork);
		pthread_mutex_unlock(&thread->firts_fork->fork);
		return (1);
	}
	set_long(&thread->mtx_philo, &thread->last_meal, get_current_time(MILISEC));
	ft_putlog(thread, thread->last_meal, EATING);
	ft_usleep(main, main->t_t_eat);
	increment_int(&thread->mtx_philo, &thread->meals, 1);
	pthread_mutex_unlock(&thread->second_fork->fork);
	pthread_mutex_unlock(&thread->firts_fork->fork);
	if (main->n_meals == thread->meals)
	{
		set_bool(&thread->mtx_philo, &thread->full, 1);
		return (0);
	}
	ft_putlog(thread, 1, SLEEPING);
	ft_usleep(main, main->t_t_sleep);
	return (0);
}

void	wait_all_childs(t_philos *main)
{
	while (get_current_time(MILISEC) < main->t_t_start)
		usleep(100);
}

int	thinking(t_childs *thread, t_philos *main, int silent_mode)
{
	if (thread->full || get_bool(&main->global, &main->stop_dinner))
		return (1);
	if (silent_mode)
		ft_usleep(main, main->t_t_eat);
	else
	{
		ft_putlog(thread, thread->id, THINKING);
		ft_usleep(main, main->t_t_think);
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
	if (main->n_meals == 0)
		return (set_bool(&thread->mtx_philo, &thread->full, 1), NULL);
	if (main->n_philos == 1)
	{
		ft_usleep(main, main->t_t_die + 100);
		return (NULL);
	}
	if (thread->id % 2 == 0)
		ft_usleep(main, main->t_t_eat);
	while (!get_bool(&main->global, &main->stop_dinner))
	{
		try_to_eat(thread, main);
		thinking(thread, main, 0);
		if (thread->full)
			break ;
	}
	return (NULL);
}
