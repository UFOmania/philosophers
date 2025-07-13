/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:11:33 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/13 17:50:12 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(pthread_t *threads, int count)
{
	int	i;

	i = -1;
	while (++i <= count)
		pthread_join(*(threads + i), NULL);
}

int	lunch_threads(pthread_t **threads, t_philosopher *philos, int count, void*(*philo_brain)(void*))
{
	int	i;
	int	state;
	
	*threads = malloc(sizeof(pthread_t) * (count + 1));
	if (!*threads)
		return (perror("error: malloc threads"), R_FAIL);
	i = -1;
	while (++i < count)
	{
		(philos + i)->last_meal = get_current_time();
		state = pthread_create(*threads + i, NULL, philo_brain, philos + i);
		if (state != 0)
		{
			perror("error: create threads");
			while (--i >= 0)
				pthread_detach(*(*(threads + i)));
			return (R_FAIL);
		}
	}
	pthread_create(*threads + i, NULL, the_observer, philos);
	//protect in the future
	return (R_SUCCESS);
}