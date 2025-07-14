/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_brain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:12:20 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/14 23:34:32 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philosopher *philo, int id)
{
	if ((id & 1))
	{
		pthread_mutex_lock(philo->left_fork);
		put_log(philo, " has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		put_log(philo, " has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		put_log(philo, " has taken a fork\n");
		pthread_mutex_lock(philo->left_fork);
		put_log(philo, " has taken a fork\n");
	}
}

static void	unlock_forks(t_philosopher *philo, int id)
{
	if ((id & 1) == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

int	single_philo(t_philosopher *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		put_log(philo, " has taken a fork\n");
		usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	eating(t_philosopher *philo)
{
	lock_forks(philo, philo->id);
	put_log(philo, " is eating\n");
	if (ft_usleep(philo, philo->time_to_eat) == 0)
	{
		unlock_forks(philo, philo->id);
		return (0);
	}
	set_last_meal(philo);
	unlock_forks(philo, philo->id);
	return (1);
}

void	*philo_brain(void *args)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)args;
	if (single_philo(philo))
		return (NULL);
	if ((philo->id & 1))
		usleep(100);
	while (1)
	{
		if (eating(philo) == 0)
			break ;
		if (is_all_done(philo))
			break ;
		put_log(philo, " is sleeping\n");
		if (ft_usleep(philo, philo->time_to_sleep) == 0)
			break ;
		put_log(philo, " is thinking\n");
	}
	return (NULL);
}
