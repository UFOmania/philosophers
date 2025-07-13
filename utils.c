/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:22:04 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/13 18:14:07 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_dead(t_philosopher *philo)
{
	pthread_mutex_lock(philo->state_lock);
	if (philo->state == -1)
		return (pthread_mutex_unlock(philo->state_lock), 1);
	pthread_mutex_unlock(philo->state_lock);
	return (0);
}