/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:33:50 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/10 15:40:23 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int	double_pointer_len(char **s)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (s[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	verify_arguments(char **argv)
{
	int	i;
	int	n;

	i = 1;
	while (argv[i])
	{
		n = ft_atoi(argv[i]);
		if (!n && argv[i][0] != '0')
			return (1);
		if (n < 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_main(t_philos *main, char **argv, int argc)
{
	if (argc == 6)
		main->n_meals = ft_atoi(argv[argc - 1]);
	else
		main->n_meals = -1;
	main->errno = 0;
	main->n_philos = ft_atoi(argv[1]);
	main->t_t_die = ft_atoi(argv[2]);
	main->t_t_eat = ft_atoi(argv[3]);
	main->t_t_sleep = ft_atoi(argv[4]);
	main->t_t_think = 1000;
	main->childs = NULL;
	main->forks = NULL;
	main->someone_died = 0;
	main->stop_dinner = 0;
}

void	abort_exec(t_philos *main)
{
	if (main->forks)
		free(main->forks);
	if (main->childs)
		free(main->childs);
}

int	main(int argc, char **argv)
{
	t_philos	main;
	t_childs	monitor;

	if (argc > 6 || argc < 5)
	{
		printf("Incorrect number of arguments.\n");
		return (1);
	}
	if (verify_arguments(argv))
		return (printf("Invalid argument/s.\n"), 1);
	init_main(&main, argv, argc);
	if (init_threads(&main))
		return (abort_exec(&main), main.errno);
	if (create_threads(&main, &monitor))
		return (abort_exec(&main), main.errno);
	return (main.errno);
}
