/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:14:24 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/04 18:41:17 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(t_mode mode)
{
	struct timeval	current_t;

	(void)mode;
	if (gettimeofday(&current_t, NULL))
		return (-1);
	return (current_t.tv_sec * 1000 + current_t.tv_usec / 1000);
	//if (mode == MILISEC)
	/*
	if (mode == MICROSEC)
		return (current_t.tv_sec * 1000000 + current_t.tv_usec);
	*/
	return (42);
}
