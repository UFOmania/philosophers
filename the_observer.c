/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_observer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:51:25 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/13 23:49:14 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (((time.tv_usec / 1000) + (time.tv_sec * 1000)));
}

void kill_the_philo(t_philosopher *philo)
{
	pthread_mutex_lock(philo->state_lock);
	philo->state = -1;
	pthread_mutex_unlock(philo->state_lock);
	// printf("killing %d \n", philo->id);
}


int	update_philo_death_state(t_philosopher *philo)
{
	long	current;
	int	state;

	usleep(400);
	state = 1;
	current = get_current_time();
	pthread_mutex_lock(philo->last_meal_lock);

	if ((current - philo->last_meal) >= philo->time_to_die)
	{
		// printf("current: %ld, last_meal: %ld, time_to_die: %ld, diff: %ld => (%ld > %ld)\n",
		// 		current,
		// 		philo->last_meal,
		// 		philo->time_to_die,
		// 		current - philo->last_meal,
		// 		current - philo->last_meal,
		// 		philo->time_to_die
		// 	);
		// kill_the_philo(philo);
		state = 0;
	}
	pthread_mutex_unlock(philo->last_meal_lock);
	// printf("check_deth_state %d >> %d\n",philo->id, state);
	return (state);
}

void	end_the_simulation(t_philosopher *philos)
{
	int	i;

	i = -1;
	while (++i < philos->philos_count)
		kill_the_philo(philos + i);
}

void	*the_observer(void *data)
{
	t_philosopher *philos;

	philos = (t_philosopher *)data;
	int	state;
	int	i;
	int	time;
	int	count;
	count = philos->philos_count;
	usleep(200);
	// start = get_current_time();
	state = 1;
	// kill_the_philo(philos + 1);
	// printf("the observer has been started with  %d\n", count);
	int	finished_philos;
	while (state)
	{
		i = -1;
		finished_philos = count;
		while (++i < count)
		{
			if (is_philo_dead(philos + i) == 0)
			{
				if (update_philo_death_state(philos + i) == 0)
				{
					put_death_log(philos + i);
					end_the_simulation(philos);
					state = 0;
					break ;
				}
			}
			else
				finished_philos--;
			if (finished_philos == 0)
				return (printf("all done!!!\n"), NULL);
		}
		usleep(100);
	}
	return (NULL);
}
