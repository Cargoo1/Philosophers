/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:21:25 by acamargo          #+#    #+#             */
/*   Updated: 2025/11/03 15:30:25 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	cifra(long nbr)
{
	long	len;

	len = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		len++;
	}
	else if (nbr == 0)
		len++;
	while (nbr > 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

static void	revtab(char *num, long n)
{
	long	i;
	long	len;
	char	temp;

	len = cifra(n) - 1;
	i = 0;
	if (n < 0)
		i++;
	while (len > i)
	{
		temp = num[i];
		num[i] = num[len];
		num[len] = temp;
		i++;
		len--;
	}
}

char	*ft_ltoa(long n)
{
	char	*num;
	long	len;
	long	i;
	long	nbr;

	i = 0;
	nbr = n;
	len = cifra(nbr);
	num = (char *)malloc((len + 1) * sizeof(char));
	if (!num)
		return (NULL);
	if (nbr == 0)
		num[i++] = 48;
	if (nbr < 0)
	{
		nbr *= -1;
		num[i++] = '-';
	}
	while (nbr > 0)
	{
		num[i++] = 48 + (nbr % 10);
		nbr = nbr / 10;
	}
	num[i] = '\0';
	return (revtab(num, n), num);
}
/*
#include<limits.h>
#include<stdio.h>
int	main()
{
	char *p=ft_itoa(INT_MIN);
	printf("%s", p);
}
*/
