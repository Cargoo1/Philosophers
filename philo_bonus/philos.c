/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:50 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/12 20:45:20 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

long	get_current_time()
{
	struct timeval	current_t;

	if (gettimeofday(&current_t, NULL))
		return (-1);
	return (current_t.tv_sec * 1000 + current_t.tv_usec / 1000);
}

void	wait_all_children(t_philos *main)
{
	while (get_current_time() < main->t_t_start)
		usleep(100);
}

int	im_i_dead(t_child *philo)
{
	if (get_current_time() - philo->last_meal > philo->main->t_t_die)
		return (1);
	return (0);
}

void	ft_usleep(t_child *philo, long time)
{
	long	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < time && (!im_i_dead(philo)))
		usleep(100);
}

int	eating(t_child *philo, t_philos *main)
{
	sem_wait(main->forks);
	ft_putlog(philo, PICKED);
	sem_wait(main->forks);
	ft_putlog(philo, PICKED);
	if (im_i_dead(philo))
	{
		sem_post(main->forks);
		sem_post(main->forks);
		return (1);
	}
	philo->last_meal = get_current_time();
	ft_putlog(philo, EATING);
	ft_usleep(philo, main->t_t_eat);
	sem_post(main->forks);
	sem_post(main->forks);
	if (im_i_dead(philo))
		return (1);
	ft_putlog(philo, SLEEPING);
	ft_usleep(philo, main->t_t_sleep);
	return (0);
}

void	start_routine(t_philos *main, int id)
{
	t_child	philo;

	sem_wait(main->someone_died);
	philo.last_meal = main->t_t_start;
	philo.id = id;
	philo.main = main;
	wait_all_children(main);
	if (philo.id % 2 == 0)
		ft_usleep(&philo, main->t_t_eat);
	ft_putlog(&philo, THINKING);
	ft_usleep(&philo, 500);
	while (!im_i_dead(&philo))
	{
		eating(&philo, main);
	}
	sem_unlink(main->sem_forks);
	sem_close(main->forks);
	free(main->pids);
	sem_wait(main->print_dead);
	ft_putlog(&philo, DIED);
	sem_post(main->someone_died);
	/*
	sem_unlink(main->sem_start);
	sem_unlink(main->sem_forks);
	sem_close(main->start);
	sem_close(main->forks);
	*/
	//free(main->pids);
	exit(0);
}

int	create_philos(t_philos *main)
{
	int	i;

	i = 0;
	main->pids = malloc(sizeof(int) * (main->n_philos));
	if (!main->pids)
		return (main->errno = ERNOMEM, ERNOMEM);
	main->t_t_start = get_current_time() + main->n_philos * 10;
	while (i < main->n_philos)
	{
		main->pids[i] = fork();
		if (main->pids[i] < 0)
			return (main->errno = ERFORK, ERFORK);
		if (main->pids[i] == 0)
			start_routine(main, i + 1);
		i++;
	}
	/*
	i = 0;
	while (i < main->n_philos)
	{
		waitpid(main->pids[i], NULL, 0);
		i++;
	}
	*/
	wait_all_children(main);
	sem_wait(main->someone_died);
	i = 0;
	while (i < main->n_philos)
	{
		kill(main->pids[i], SIGKILL);
		i++;
	}
	sem_unlink(main->sem_print_dead);
	sem_unlink(main->sem_putlog);
	sem_unlink(main->sem_s_died);
	sem_unlink(main->sem_forks);
	sem_close(main->print_dead);
	sem_close(main->putlog);
	sem_close(main->forks);
	sem_close(main->someone_died);
	free(main->pids);
	return (0);
}
