/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:14:24 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/27 15:31:49 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_current_time(t_philos *main)
{
	int				time;
	int				ref;
	struct timeval	current_t;

	gettimeofday(&current_t, NULL);
	ref = main->reference.tv_usec / 1000;
	time = current_t.tv_usec / 1000;
	time = time - ref;
	return (time);
}
