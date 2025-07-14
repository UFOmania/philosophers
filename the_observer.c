/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_observer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:51:25 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/14 13:53:37 by massrayb         ###   ########.fr       */
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
	int		state;

	state = 1;
	current = get_current_time();
	pthread_mutex_lock(philo->last_meal_lock);

	if ((current - philo->last_meal) > philo->time_to_die)
		state = 0;
	pthread_mutex_unlock(philo->last_meal_lock);
	return (state);
}

void	end_the_simulation(t_obs_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philos->philos_count)
		kill_the_philo(args->philos + i);
	
	args->state = 0;
}

t_obs_args init_observer(t_philosopher *philos)
{
	t_obs_args	args;

	args.philos = philos;
	args.i = -1;
	args.count = philos->philos_count;
	args.finished_philos = args.count;
	args.state = 1;
	return (args);
}

void	*the_observer(void *data)
{
	t_obs_args	args;

	args = init_observer((t_philosopher *)data);
	while (args.state)
	{
		args.i = -1;
		args.finished_philos = args.count;
		while (++args.i < args.count)
		{
			if (is_philo_dead(args.philos + args.i) == 0)
			{
				if (update_philo_death_state(args.philos + args.i) == 0)
				{
					end_the_simulation(&args);
					put_death_log(args.philos + args.i, " died\n");
					break ;
				}
			}
			else
				args.finished_philos--;
			if (args.finished_philos == 0)
				return (printf("all done!!!\n"), NULL);
		}
		usleep(100);
	}
	return (NULL);
}
