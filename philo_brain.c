/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_brain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:12:20 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/13 23:00:46 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_is_starving(t_philosopher *philo)
{
	int	starve;

	pthread_mutex_lock(philo->starving_lock);
	starve = philo->is_starving;
	pthread_mutex_unlock(philo->starving_lock);
	return (starve);
}

static void	set_is_starving(t_philosopher *philo, int value)
{
	pthread_mutex_lock(philo->starving_lock);
	philo->is_starving = value;
	pthread_mutex_unlock(philo->starving_lock);
}

static int	get_philo_state(t_philosopher *philo)
{
	int	state;

	pthread_mutex_lock(philo->state_lock);
	state = philo->state;
	pthread_mutex_unlock(philo->state_lock);
	return (state);
}

static void	lock_forks(t_philosopher *philo, int flag)
{
	if (flag % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		put_fork_log(philo);
		pthread_mutex_lock(philo->right_fork);
		put_fork_log(philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		put_fork_log(philo);
		pthread_mutex_lock(philo->left_fork);
		put_fork_log(philo);
	}
}

static void	unlock_forks(t_philosopher *philo, int flag)
{
	if (flag % 2)
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

static void	set_last_meal(t_philosopher *philo)
{
	pthread_mutex_lock(philo->last_meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->last_meal_lock);
}

void	*philo_brain(void *args)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)args;
	if (philo->id % 2 == 0) usleep(philo->time_to_eat / 2);
	while (1)
	{
		put_think_log(philo);
		if (philo->left_fork == philo->right_fork)
		{
			if (ft_usleep(philo,  philo->time_to_die + 100) == 0)
				break;
		}
		lock_forks(philo, philo->id);
		put_eat_log(philo);
		if (ft_usleep(philo, philo->time_to_eat) == 0)
		{
			unlock_forks(philo, 0);
			break;
		}
		unlock_forks(philo, philo->id);
		set_last_meal(philo);
		if (philo->num_times_must_eat != -1)
		{
			philo->num_times_must_eat--;
			if (philo->num_times_must_eat == 0)
			{
				kill_the_philo(philo);
				break;
			}
		}
		put_sleep_log(philo);
		if (ft_usleep(philo, philo->time_to_sleep) == 0)
			break;
	}
	return (NULL);
}
