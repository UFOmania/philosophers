/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:26:11 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/13 23:49:52 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_philosopher *philo, int amount)
{
	long	start;
	long	current;
	

	start = get_current_time();
	while (1)
	{
		current = get_current_time();
		if ((current - start) < amount)
			usleep(50);
		else
			break ;
		if(is_philo_dead(philo))
			return (0);
	}
	return (1);
}