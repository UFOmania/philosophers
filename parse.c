/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:35:03 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/14 23:32:00 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+')
		i++;
	else if (str[0] == '-')
		return (printf("error: invalid arguments\n"), 0);
	else if (str[0] == '\0')
		return (printf("error: invalid arguments\n"), 0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (printf("error: invalid arguments\n"), 0);
		i++;
	}
	if (str[i - 1] < '0' || str[i - 1] > '9')
		return (printf("error: invalid arguments\n"), 0);
	return (1);
}

static int	extract_value(char *str, int *nbr)
{
	if (is_digit(str))
	{
		*nbr = ft_atoi(str);
		if (*nbr <= 0)
			return (printf("error: invalid arguments\n"), R_FAIL);
	}
	else
		return (R_FAIL);
	return (R_SUCCESS);
}

int	parse_args(t_args *args, int ac, char **av)
{
	*args = (t_args){0};
	if (extract_value(av[0], &args->philos_count) == R_FAIL)
		return (R_FAIL);
	if (extract_value(av[1], &args->time_to_die) == R_FAIL)
		return (R_FAIL);
	if (extract_value(av[2], &args->time_to_eat) == R_FAIL)
		return (R_FAIL);
	if (extract_value(av[3], &args->time_to_sleep) == R_FAIL)
		return (R_FAIL);
	if (ac == 6)
	{
		if (extract_value(av[4], &args->num_times_must_eat) == R_FAIL)
			return (R_FAIL);
	}
	else
		args->num_times_must_eat = -1;
	return (R_SUCCESS);
}
