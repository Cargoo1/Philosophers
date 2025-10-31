/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:45:36 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/31 17:05:59 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_philos *main, int *boolean, int value)
{
	change_mtx(&main->global, LOCK);
	*boolean = value;
	change_mtx(&main->global, UNLOCK);
}

void	set_int(t_philos *main, int *num, int value)
{
	if (change_mtx(&main->global, LOCK))
		return;
	*num = value;
	if (change_mtx(&main->global, UNLOCK))
		return;
}

void	increment_int(t_philos *main, int *num, int value)
{
	if (change_mtx(&main->global, LOCK))
		return;
	*num += value;
	if (change_mtx(&main->global, UNLOCK))
		return;
}

void	set_long(t_philos *main, long *num, long value)
{
	if (change_mtx(&main->global, LOCK))
		return;
	*num = value;
	if (change_mtx(&main->global, UNLOCK))
		return;
}
