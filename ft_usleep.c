/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:26:11 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/14 21:47:41 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_philosopher *philo, long amount)
{
	long	start;

	start = get_current_time();
	while (1)
	{
		if (get_current_time() - start >= amount)
			break ;
		if (is_philo_dead(philo))
			return (0);
		usleep(100);
	}
	return (1);
}
