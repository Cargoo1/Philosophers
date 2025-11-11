/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:57:51 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/11 17:41:02 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int	test(sem_t *forks, int id)
{
	sem_wait(forks);
	sleep(1);
	printf("hola: %d\n", id);
	sem_post(forks);
	return (0);
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

int	init_main(t_philos *main)
{

}

int	main(int argc, char **argv)
{
	t_philos	main;

	if (argc > 6 || argc < 5)
	{
		printf("Wrong number of arguments.\n");
		return (1);
	}
	if (verify_arguments(argv))
		return (1);
	init_main(&main);
}
