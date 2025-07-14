/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:22:04 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/14 23:28:17 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_dead(t_philosopher *philo)
{
	pthread_mutex_lock(philo->locks + LOCK_STATE);
	if (philo->state == -1)
		return (pthread_mutex_unlock(philo->locks + LOCK_STATE), 1);
	pthread_mutex_unlock(philo->locks + LOCK_STATE);
	return (0);
}

void	kill_the_philo(t_philosopher *philo)
{
	pthread_mutex_lock(philo->locks + LOCK_STATE);
	philo->state = -1;
	pthread_mutex_unlock(philo->locks + LOCK_STATE);
}

void	end_the_simulation(t_obs_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philos->philos_count)
		kill_the_philo(args->philos + i);
	args->state = 0;
}

void	set_last_meal(t_philosopher *philo)
{
	pthread_mutex_lock(philo->locks + LOCK_TIME);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->locks + LOCK_TIME);
}

int	is_all_done(t_philosopher *philo)
{
	if (philo->num_times_must_eat != -1)
	{
		philo->num_times_must_eat--;
		if (philo->num_times_must_eat == 0)
		{
			kill_the_philo(philo);
			return (1);
		}
	}
	return (0);
}
