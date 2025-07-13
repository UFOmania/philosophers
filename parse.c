/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:35:03 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/13 23:42:19 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int is_digit(char *str)
{
	int				i;

	i = 0;
	if (str[0] == '+')
		i++;
	else if (str[0] == '-')
		return (printf("error: invalid arguments \"unsigned values only\"\n"), 0);
	else if (str[0] == '\0')
		return (printf("error: invalid arguments \"empty valus is invalid\" \n"), 0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (printf("error: invalid arguments \"digits only\" \n"), 0);
		i++;
	}
	if (str[i - 1] < '0' || str[i - 1] > '9')
		return (printf("error: invalid arguments \"found no digit\" \n"), 0);
	return (1);
}

int	parse_args(t_args *args, int ac, char **av)
{

	*args = (t_args){0};
	if (is_digit(av[0]))
	{
		if ((args->philos_count = ft_atoi(av[0])) == 0)
			return (printf("error: invalid arguments \"philos_count must be more then 0\" \n"), R_FAIL);
	}
	else
		return (R_FAIL);
	if (is_digit(av[1]))
		args->time_to_die = ft_atoi(av[1]);
	else
		return (R_FAIL);
	if (is_digit(av[2]))
		args->time_to_eat = ft_atoi(av[2]);
	else
		return (R_FAIL);
	if (is_digit(av[3]))
		args->time_to_sleep = ft_atoi(av[3]);
	else
		return (R_FAIL);
	if (ac == 6)
	{
		if (is_digit(av[4]))
		{
			args->num_times_must_eat = ft_atoi(av[4]);
			if (args->num_times_must_eat == 0)
				return (printf("error: invalid arguments \"number_of_times_each_philosopher_must_eat must be more then 0\" \n"), R_FAIL);
		}
		else
			return (R_FAIL);
	}
	else
		args->num_times_must_eat = -1;
	return (R_SUCCESS);
}
