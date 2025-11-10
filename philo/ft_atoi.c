/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:41:02 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/03 19:37:47 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"

static int	ft_str_is_numeric(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

static int	convertion(char *str, int sign)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (ft_str_is_numeric(str[i]))
	{
		if (num > INT_MAX / 10 || (num == INT_MAX / 10 && str[i] - '0' > 7))
		{
			if ((sign == -1 && num > INT_MAX / 10)
				|| (num == INT_MAX / 10 && str[i] - '0' > 8))
				return (INT_MIN);
			else
				return (INT_MAX);
		}
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	int		numero;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	numero = convertion(&str[i], sign);
	return (numero);
}
