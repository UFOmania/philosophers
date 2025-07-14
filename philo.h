/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:26:12 by massrayb          #+#    #+#             */
/*   Updated: 2025/07/14 23:33:53 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h> // why nigga
# include <errno.h>// why nigga
# include <pthread.h>
# include <sys/time.h>

# define DEAD 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define TOOK_FORK 4
# define R_FAIL 0
# define R_SUCCESS 1
# define LOCKS_COUNT 4
# define LOCK_TIME 0
# define LOCK_STATE 1
# define LOCK_LOG 2
# define LOCK_STARVE 3

typedef struct s_args
{
	int			start_time;
	int			philos_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_times_must_eat;
}	t_args;

typedef struct s_philosopher
{
	int				id;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_times_must_eat;
	long			last_meal;
	int				eat_so_far;
	int				state;
	int				is_starving;
	int				black_hole;
	int				philos_count;
	pthread_mutex_t	*locks;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}				t_philosopher;

typedef struct s_table
{
	pthread_t		*threads;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
}					t_table;

typedef struct s_obs_args
{
	t_philosopher	*philos;
	int				state;
	int				i;
	int				count;
	int				finished_philos;
}				t_obs_args;

//parse
int			parse_args(t_args *args, int ac, char **av);

//ft_atoi
int			ft_atoi(const char *str);

//clear
void		destroy_forks(pthread_mutex_t *forks, int count);
void		destroy_locks(pthread_mutex_t *locks);

// init_table
int			init_table(t_args args, t_philosopher **philos, \
pthread_mutex_t **forks);

// lunch threads
int			lunch_threads(pthread_t **threads, t_philosopher \
*philos, int count, void*(*philo_brain)(void*));
void		wait_threads(pthread_t *threads, int count);

//philo_brain
void		*philo_brain(void *philo);
void		*the_observer(void *data);
long		get_current_time(void);

//log
void		put_death_log(t_philosopher *philo, char *log);
void		put_log(t_philosopher *philo, char *log);

//ft_usleep
int			ft_usleep(t_philosopher *philo, long amount);

//utils
int			is_philo_dead(t_philosopher *philo);
int			get_is_starving(t_philosopher *philo);
void		kill_the_philo(t_philosopher *philo);
void		end_the_simulation(t_obs_args *args);
t_obs_args	init_observer(t_philosopher *philos);
void		set_last_meal(t_philosopher *philo);
int			is_all_done(t_philosopher *philo);

#endif
