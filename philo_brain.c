/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_brain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:12:20 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/14 13:28:44 by massrayb         ###   ########.fr       */
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
	if ((flag & 1) == 0 && (philo->left_fork))
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

static void	unlock_forks(t_philosopher *philo, int flag)
{
	if ((flag & 2) == 0)
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

int	alone_wolf(t_philosopher *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		put_log(philo, " has taken a fork\n");
		if (ft_usleep(philo,  philo->time_to_die + 100) == 0)
			return (pthread_mutex_unlock(philo->left_fork), 1);
	}
	return (0);
}
int	all_done(t_philosopher *philo)
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

int meal_time_fatality(t_philosopher *philo)
{
	if (ft_usleep(philo, philo->time_to_eat) == 0)
	{
		unlock_forks(philo, 0);
		return (1);
	}
	return (0);
}


void	*philo_brain(void *args)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)args;
	if ((philo->id & 1)) 
		ft_usleep(philo, 10);
	if (alone_wolf(philo))
		return (NULL);
	while (1)
	{
		if ((philo->id & 1) == 0)
			usleep(10);
		lock_forks(philo, philo->id);
		put_log(philo, " is eating\n");
		if (meal_time_fatality(philo))
			return (NULL);
		set_last_meal(philo);
		unlock_forks(philo, philo->id);
		put_log(philo, " is sleeping\n");
		if(all_done(philo))
			return (NULL);
		if (ft_usleep(philo, philo->time_to_sleep) == 0)
			break;
		put_log(philo, " is thinking\n");
	}
	return (NULL);
}
