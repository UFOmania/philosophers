/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:46:02 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/14 11:10:13 by massrayb         ###   ########.fr       */
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

static int	handle_numbers(const char *s, int index)
{
	int	tmp;
	int	res;

	tmp = 0;
	res = 0;
	while (s[index] >= '0' && s[index] <= '9')
	{
		tmp = res;
		res *= 10;
		res += (s[index] - '0');
		if (res < tmp)
			return (-1);
		index++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	i = handle_white_spaces(str, i);
	result = handle_numbers(str, i);
	return (result);
}