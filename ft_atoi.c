/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acamargo <acamargo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:41:02 by acamargo          #+#    #+#             */
/*   Updated: 2025/10/22 18:22:13 by acamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_str_is_numeric(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

static long	potencia(int n)
{
	long	base10;

	base10 = 1;
	while (n-- > 1)
		base10 *= 10;
	return (base10);
}

static long	convertion(char *str)
{
	int		i;
	int		cifra;
	long	num;

	i = 0;
	cifra = 0;
	num = 0;
	while (ft_str_is_numeric(str[cifra]))
		cifra++;
	while (ft_str_is_numeric(str[i]))
	{
		num += (str[i] - '0') * potencia(cifra--);
		i++;
	}
	return (num);
}

long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	numero;

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
	numero = convertion(&str[i]);
	return (numero * sign);
}
