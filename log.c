/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:19:27 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/13 21:26:18 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_death_log(t_philosopher *philo)
{
	pthread_mutex_lock(philo->log_lock);
	printf("%ld %d died\n", get_current_time() - philo->start_time, philo->id); //update the to write in the future
	pthread_mutex_unlock(philo->log_lock);
}

void	put_eat_log(t_philosopher *philo)
{
	pthread_mutex_lock(philo->log_lock);
	if (is_philo_dead(philo))
	{
		pthread_mutex_unlock(philo->log_lock);	
		return ;
	}
	printf("%ld %d is eating\n", get_current_time() - philo->start_time, philo->id); //update the to write in the future
	pthread_mutex_unlock(philo->log_lock);
}

void	put_sleep_log(t_philosopher *philo)
{
	pthread_mutex_lock(philo->log_lock);
	if (is_philo_dead(philo))
	{
		pthread_mutex_unlock(philo->log_lock);	
		return ;
	}
	printf("%ld %d is sleeping\n", get_current_time() - philo->start_time, philo->id); //update the to write in the future
	pthread_mutex_unlock(philo->log_lock);
}

void	put_think_log(t_philosopher *philo)
{
	pthread_mutex_lock(philo->log_lock);
	if (is_philo_dead(philo))
	{
		pthread_mutex_unlock(philo->log_lock);	
		return ;
	}
	printf("%ld %d is thinking\n", get_current_time() - philo->start_time, philo->id); //update the to write in the future
	pthread_mutex_unlock(philo->log_lock);
}

void	put_fork_log(t_philosopher *philo)
{
	pthread_mutex_lock(philo->log_lock);
	if (is_philo_dead(philo))
	{
		pthread_mutex_unlock(philo->log_lock);	
		return ;
	}
	printf("%ld %d has taken a fork\n", get_current_time() - philo->start_time, philo->id); //update the to write in the future
	pthread_mutex_unlock(philo->log_lock);
}
