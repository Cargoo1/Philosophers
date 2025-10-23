/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:33:50 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/23 11:48:25 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	*verify_arguments(char **argv)
{
	int	i;
	int	j;
	int	*args_lst;
	int	args_count;

	i = 1;
	args_count = double_pointer_len(argv);
	while (argv[i])
	{
		if (!ft_atoi(argv[i]) && argv[i][0] != '0')
			return (NULL);
		i++;
	}
	i = 1;
	j = 0;
	args_lst = malloc(sizeof(int) * args_count);
	if (!args_lst)
		return (NULL);
	while (argv[i])
	{
		args_lst[j] = ft_atoi(argv[i]);
		j++;
		i++;
	}
	return (args_lst);
}

void	*start_routine(void *args)
{
	struct timeval	curr_t;
	sleep(2);
	gettimeofday(&curr_t, NULL);
	printf("%lu", curr_t.tv_sec);
	printf("%s\n", (char *)args);
	return (NULL);
}

int	init_threads(s_philos *main)
{
	int				i;

	i = 0;
	main->threads = malloc(sizeof(pthread_t) * *main->arguments);
	if (!main->threads)
		return (ERMALLOC);
	if (gettimeofday(&main->reference, NULL))
		return (1);
	while (i < *main->arguments)
	{
		if (pthread_create(&main->threads[i], NULL, start_routine, main))
			return (ERTHREAD);
		i++;
	}
	i = 0;
	while (i < *main->arguments)
	{
		pthread_join(main->threads[i], NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	s_philos		main;

	if (argc > 6 || argc < 5)
	{
		printf("Incorrect number of arguments");
		return (1);
	}
	main.arguments = verify_arguments(argv);
	if (!main.arguments)
		return (FAILURE);
	init_threads(&main);
}
