/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:35:29 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/10 15:21:03 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = -1;
	while (++i)
		pthread_mutex_destroy(forks + i);
	free(forks);
}

void	destroy_locks(pthread_mutex_t *locks)
{
	int	i;

	i = -1;
	while (++i < LOCKS_COUNT)
		pthread_mutex_destroy(locks + i);
	free(locks);
}