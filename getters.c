/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:41:23 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/30 14:13:25 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_bool(t_philos *main, int *boolean)
{
	int	res;

	change_mtx(&main->global, LOCK);
	res = *boolean;
	change_mtx(&main->global, UNLOCK);
	return (res);
}

int	get_int(t_philos *main, int *num)
{
	int	res;
	if (change_mtx(&main->global, LOCK))
		return (1);
	res = *num;
	if (change_mtx(&main->global, UNLOCK))
		return (1);
	return (res);
}

long	get_long(t_philos *main, long *num)
{
	long	res;
	
	if (change_mtx(&main->global, LOCK))
		return (1);
	res = *num;
	if (change_mtx(&main->global, UNLOCK))
		return (1);
	return (res);
}
