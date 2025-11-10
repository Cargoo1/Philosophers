/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:14:24 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/10 17:46:45 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(t_mode mode)
{
	struct timeval	current_t;

	if (gettimeofday(&current_t, NULL))
		return (-1);
	if (mode == MILISEC)
		return (current_t.tv_sec * 1000 + current_t.tv_usec / 1000);
	if (mode == MICROSEC)
		return (current_t.tv_sec * 1000000 + current_t.tv_usec);
	return (42);
}
