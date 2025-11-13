/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:57:51 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/13 21:20:06 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

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

int	init_main(t_philos *main, char **argv, int argc)
{
	main->errno = 0;
	main->n_philos = ft_atoi(argv[1]);
	main->t_t_die = ft_atoi(argv[2]);
	main->t_t_eat = ft_atoi(argv[3]);
	main->t_t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		main->n_meals = ft_atoi(argv[5]);
	else
		main->n_meals = -1;
	main->sem_forks = "forks";
	main->sem_print_dead = "print_dead";
	main->sem_putlog = "putlog";
	main->sem_s_died = "dead";
	sem_unlink(main->sem_forks);
	sem_unlink(main->sem_s_died);
	sem_unlink(main->sem_putlog);
	sem_unlink(main->sem_print_dead);
	main->forks = sem_open(main->sem_forks, O_CREAT, 0666, main->n_philos);
	if (main->forks == SEM_FAILED)
		return (main->errno = ERSEM, ERSEM);
	main->print_dead = sem_open(main->sem_print_dead, O_CREAT, 0666, 1);
	if (main->print_dead == SEM_FAILED)
		return (main->errno = ERSEM, ERSEM);
	main->someone_died = sem_open(main->sem_s_died, O_CREAT, 0666, main->n_philos);
	if (main->someone_died == SEM_FAILED)
		return (main->errno = ERSEM, ERSEM);
	main->putlog = sem_open(main->sem_putlog, O_CREAT, 0666, 1);
	if (main->putlog == SEM_FAILED)
		return (main->errno = ERSEM, ERSEM);
	if (main->n_philos == 1)
		main->t_t_think = main->t_t_die;
	else if (main->n_philos % 2 != 0 && main->t_t_eat > main->t_t_sleep)
		main->t_t_think = (main->t_t_eat * 2) - main->t_t_sleep;
	else if (main->n_philos % 2 != 0 && main->t_t_sleep > main->t_t_eat)
		main->t_t_think = (main->t_t_eat * 2) - main->t_t_sleep;
	else if (main->n_philos % 2)
		main->t_t_think = main->t_t_eat;
	else
		main->t_t_think = 0;
	return (0);
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
	if (init_main(&main, argv, argc))
		return (main.errno);
	if (create_philos(&main))
		return (main.errno);
}
