/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:11:33 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/14 23:33:30 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_start_time(t_philosopher *philos)
{
	int		i;
	long	start;

	start = get_current_time();
	i = -1;
	while (++i < philos->philos_count)
		(philos + i)->start_time = start;
}

void	wait_threads(pthread_t *threads, int count)
{
	int	i;

	i = -1;
	while (++i <= count)
		pthread_join(*(threads + i), NULL);
}

int	lunch_threads(pthread_t **threads, t_philosopher *philos, int count, \
void*(*philo_brain)(void*))
{
	int			i;
	int			state;
	t_obs_args	args;

	init_start_time(philos);
	*threads = malloc(sizeof(pthread_t) * (count + 1));
	if (!*threads)
		return (perror("error: malloc threads 1"), R_FAIL);
	i = -1;
	while (++i < count)
	{
		(philos + i)->last_meal = get_current_time();
		state = pthread_create(*threads + i, NULL, philo_brain, philos + i);
		if (state != 0)
		{
			args = init_observer(philos);
			end_the_simulation(&args);
			pthread_mutex_lock(philos->locks + LOCK_LOG);
			perror("error: create threads 2");
			pthread_mutex_unlock(philos->locks + LOCK_LOG);
			return (wait_threads(*threads, count), R_FAIL);
		}
	}
	pthread_create(*threads + i, NULL, the_observer, philos);
	return (R_SUCCESS);
}
