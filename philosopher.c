/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:41:51 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/14 21:47:03 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args			args;
	t_philosopher	*philos;
	pthread_mutex_t	*forks;
	pthread_t		*threads;

	if (ac < 5 || ac > 6)
		return (write(2, "invalid arguments count\n", 25), 1);
	if (parse_args(&args, ac, av + 1) == R_FAIL)
		return (1);
	if (init_table(args, &philos, &forks) == R_FAIL)
		return (1);
	if (lunch_threads(&threads, philos, args.philos_count, \
	philo_brain) == R_FAIL)
		return (1);
	wait_threads(threads, args.philos_count);
}
