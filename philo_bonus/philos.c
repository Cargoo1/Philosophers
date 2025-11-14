/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:50 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/14 14:59:14 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
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
	long	goal;

	goal = get_current_time() + time;
	while (get_current_time() < goal && (!get_bool(philo->local, &philo->im_dead)))
		usleep(100);
}

int	eating(t_child *philo, t_philos *main)
{
	sem_wait(main->forks);
	ft_putlog(philo, PICKED);
	sem_wait(main->forks);
	ft_putlog(philo, PICKED);
	if (get_bool(philo->local, &philo->im_dead))
	{
		sem_post(main->forks);
		sem_post(main->forks);
		return (1);
	}
	set_long(philo->local, &philo->last_meal, get_current_time());
	ft_putlog(philo, EATING);
	ft_usleep(philo, main->t_t_eat);
	sem_post(main->forks);
	sem_post(main->forks);
	philo->meals++;
	if (philo->meals == main->n_meals)
		return (set_bool(philo->local, &philo->im_full, 1), 0);
	ft_putlog(philo, SLEEPING);
	ft_usleep(philo, main->t_t_sleep);
	return (0);
}

void	*monitoring(void *args)
{
	t_child	*philo;

	philo = (t_child *)args;
	while (!get_bool(philo->local, &philo->im_full))
	{
		long	elapsed = get_current_time() - get_long(philo->local, &philo->last_meal);
		if (elapsed > philo->main->t_t_die)
		{
			set_bool(philo->local, &philo->im_dead, 1);
			sem_wait(philo->main->print_dead);
			ft_putlog(philo, DIED);
			sem_post(philo->main->someone_died);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

int	thinking(t_child *philo, t_philos *main, int silent_mode)
{
	if (philo->im_full || get_bool(philo->local, &philo->im_dead))
		return (1);
	if (silent_mode)
		ft_usleep(philo, main->t_t_eat);
	else
	{
		ft_putlog(philo, THINKING);
		ft_usleep(philo, main->t_t_think);
		return (0);
	}
	return (0);
}

void	clean_exit(t_philos *main, t_child *philo)
{
	sem_unlink(main->sem_print_dead);
	sem_unlink(main->sem_putlog);
	sem_unlink(main->sem_s_died);
	sem_unlink(main->sem_forks);
	sem_close(main->print_dead);
	sem_close(main->putlog);
	sem_close(main->forks);
	sem_close(main->someone_died);
	free(main->pids);
	if (!philo)
		return;
	sem_unlink("local");
	sem_close(philo->local);
}

int	init_philo(t_philos *main, t_child *philo, int id)
{
	philo->last_meal = main->t_t_start;
	philo->id = id;
	philo->meals = 0;
	philo->im_full = 0;
	philo->im_dead = 0;
	philo->main = main;
	sem_unlink("local");
	philo->local = sem_open("local", O_CREAT, 0666, 1);
	if (philo->local == SEM_FAILED)
		return (1);
	return (0);
}

void	start_routine(t_philos *main, int id)
{
	t_child		philo;
	pthread_t	monitor;

	sem_wait(main->someone_died);
	if (init_philo(main, &philo, id))
		exit(1);
	pthread_create(&monitor, NULL, monitoring, &philo);
	(void)monitor;
	wait_all_children(main);
	if (philo.id % 2 == 0)
		thinking(&philo, main, 1);
	while (!get_bool(philo.local, &philo.im_dead) && !philo.im_full)
	{
		eating(&philo, main);
		thinking(&philo, main, 0);
	}
	if (get_bool(philo.local, &philo.im_dead))
		sem_wait(main->print_dead);
	pthread_join(monitor, NULL);
	clean_exit(main, &philo);
	exit(0);
}

void	*killer(void *args)
{
	t_philos	*main;
	int			i;

	main = (t_philos *)args;
	wait_all_children(main);
	sem_wait(main->someone_died);
	printf("KILL?\n");
	i = 0;
	while (i < main->n_philos)
	{
		kill(main->pids[i], SIGKILL);
		i++;
	}
	return (0);
}

int	create_philos(t_philos *main)
{
	int			i;
	pthread_t	killer_thread;

	i = 0;
	main->pids = malloc(sizeof(int) * (main->n_philos));
	if (!main->pids)
		return (main->errno = ERNOMEM, ERNOMEM);
	main->t_t_start = get_current_time() + main->n_philos * 10 * 2;
	while (i < main->n_philos)
	{
		main->pids[i] = fork();
		if (main->pids[i] < 0)
			return (main->errno = ERFORK, ERFORK);
		if (main->pids[i] == 0)
			start_routine(main, i + 1);
		i++;
	}
	if (pthread_create(&killer_thread, NULL, killer, main))
		return (1);
	i = 0;
	while (i < main->n_philos)
	{
		waitpid(main->pids[i], NULL, 0);
		i++;
	}
	sem_post(main->someone_died);
	pthread_join(killer_thread, NULL);
	clean_exit(main, NULL);
	return (0);
}
