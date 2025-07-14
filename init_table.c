/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:17:54 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/14 16:48:25 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(pthread_mutex_t **forks, int count)
{
	int	i;
	int	state;

	*forks = malloc(sizeof(pthread_mutex_t) * count);
	if (!*forks)
		return (perror("error: init forks"), R_FAIL);
	i = -1;
	while (++i < count)
	{
		state = pthread_mutex_init(*forks + i, NULL);
		if (state != 0)
		{
			perror("error: init forks");
			while (--i >= 0)
				pthread_mutex_destroy(*forks + i);
			return (free(*forks), R_FAIL);
		}
	}
	return (R_SUCCESS);
}

static int	init_locks(t_philosopher *philos, int count)
{
	int				i;
	int				state;
	pthread_mutex_t	*locks;

	locks = malloc(sizeof(pthread_mutex_t) * LOCKS_COUNT);
	if (!locks)
		return (perror("error: init locks"), R_FAIL);
	i = -1;
	while (++i < LOCKS_COUNT)
	{
		state = pthread_mutex_init((locks) + i, NULL);
		if (state != 0)
		{
			perror("error: init locks");
			while (--i >= 0)
				pthread_mutex_destroy(locks + i);
			return (free(locks), R_FAIL);
		}
	}
	i = -1;
	while (++i < count)
		(philos + i)->locks = locks;
	return (R_SUCCESS);
}

static void	assign_forks(t_philosopher *philo, int id, int count, \
pthread_mutex_t *forks)
{
	philo->right_fork = forks + id;
	if (id == count - 1)
		philo->left_fork = forks;
	else
		philo->left_fork = forks + id + 1;
}

static int	init_philos(t_philosopher **philos, t_args args, \
pthread_mutex_t *forks, pthread_mutex_t *locks)
{
	int	i;

	*philos = malloc(sizeof(t_philosopher) * args.philos_count);
	if (!*philos)
		return (perror("init philos error:"), R_FAIL);
	i = -1;
	while (++i < args.philos_count)
	{
		(*philos + i)->id = i;
		(*philos + i)->is_starving = 1;
		(*philos + i)->last_meal = 0;
		(*philos + i)->state = 0;
		(*philos + i)->num_times_must_eat = args.num_times_must_eat;
		(*philos + i)->time_to_die = args.time_to_die;
		(*philos + i)->time_to_sleep = args.time_to_sleep;
		(*philos + i)->time_to_eat = args.time_to_eat;
		(*philos + i)->philos_count = args.philos_count;
		assign_forks(*philos + i, i, args.philos_count, forks);
	}
	return (R_SUCCESS);
}

int	init_table(t_args args, t_philosopher **philos, pthread_mutex_t **forks)
{
	pthread_mutex_t	*locks;

	if (init_forks(forks, args.philos_count) == R_FAIL)
		return (R_FAIL);
	if (init_philos(philos, args, *forks, locks) == R_FAIL)
		return (destroy_forks(*forks, args.philos_count), R_FAIL);
	if (init_locks(*philos, args.philos_count) == R_FAIL)
		return (destroy_forks(*forks, args.philos_count), R_FAIL);
	return (R_SUCCESS);
}
