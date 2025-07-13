/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:46:02 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/11 18:27:56 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_white_spaces(const char *s, int i)
{
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\v' || s[i] == '\f'
		|| s[i] == '\r' || s[i] == '\n')
		i++;
	return (i);
}

static int	handle_sign(const char *s, int index, int *sign)
{
	if (s[index] == '+' || s[index] == '-')
	{
		if (s[index] == '-')
			*sign *= -1;
		index++;
	}
	return (index);
}

static long	handle_numbers(const char *s, int index, int sign)
{
	long	tmp;
	long	res;

	tmp = 0;
	res = 0;
	while (s[index] >= '0' && s[index] <= '9')
	{
		tmp = res;
		res *= 10;
		res += (s[index] - '0');
		if (res < tmp && sign == 1)
			return (-1);
		if (res < tmp && sign == -1)
			return (0);
		index++;
	}
	return (res * sign);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	i = handle_white_spaces(str, i);
	i = handle_sign(str, i, &sign);
	result = handle_numbers(str, i, sign);
	return (result);
}