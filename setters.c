/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:45:36 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/29 22:36:32 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_philos *main, int *boolean, int value)
{
	if (change_mtx(&main->global, LOCK))
		return;
	*boolean = value;
	if (change_mtx(&main->global, UNLOCK))
		return;
}

void	set_int(t_philos *main, int *num, int value)
{
	if (change_mtx(&main->global, LOCK))
		return;
	*num = value;
	if (change_mtx(&main->global, UNLOCK))
		return;
}
