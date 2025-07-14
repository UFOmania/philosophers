/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:19:27 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/14 16:37:31 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putnbr(long n)
{
	char	c;

	if (n > 9)
	{
		ft_putnbr(n / 10);
		c = (n % 10) + '0';
		write (1, &c, 1);
	}
	else
	{
		c = n + '0';
		write (1, &c, 1);
	}
}

void	put_log(t_philosopher *philo, char *log)
{
	pthread_mutex_lock(philo->locks + LOCK_LOG);
	if (is_philo_dead(philo))
	{
		pthread_mutex_unlock(philo->locks + LOCK_LOG);
		return ;
	}
	ft_putnbr(get_current_time() - philo->start_time);
	write(1, " ", 1);
	ft_putnbr((long)philo->id);
	while (*log)
	{
		write (1, log, 1);
		log++;
	}
	pthread_mutex_unlock(philo->locks + LOCK_LOG);
}

void	put_death_log(t_philosopher *philo, char *log)
{
	pthread_mutex_lock(philo->locks + LOCK_LOG);
	ft_putnbr(get_current_time() - philo->start_time);
	write(1, " ", 1);
	ft_putnbr((long)philo->id);
	while (*log)
	{
		write (1, log, 1);
		log++;
	}
	pthread_mutex_unlock(philo->locks + LOCK_LOG);
}
