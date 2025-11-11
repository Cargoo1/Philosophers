/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:52:03 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/11 17:40:06 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS

# define PHILO_BONUS

# include <fcntl.h>

# include <semaphore.h>

# include <stdio.h>

# include <unistd.h>

# include <stdlib.h>

# include <sys/wait.h>

typedef struct s_philos
{
	int		n_philos;
	int		t_t_die;
	int		t_t_eat;
	int		t_t_sleep;
	int		n_meals;
}	t_philos;

int	ft_atoi(char *str);

#endif
