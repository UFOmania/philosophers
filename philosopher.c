#include "philo.h"

void	print_args(t_args args)
{
	printf("philos count :%d\ntime to die :%ld\ntime to eat :%ld\ntime to sleep :%ld\ntimes_must_eat :%d\n", args.philos_count, args.time_to_die, args.time_to_eat, args.time_to_sleep, args.num_times_must_eat);
}



int main(int ac, char **av)
{
	t_args			args;
	t_philosopher	*philos;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	int				is_done;

	is_done = 0;
	if (ac < 5 || ac > 6)
		return (write(2, "invalid arguments count\n", 25), 1);
	if (parse_args(&args, ac, av + 1) == R_FAIL)
		return (1);
	print_args(args);
	if (init_table(args, &philos, &forks, &is_done) == R_FAIL)
		return (1);
	long start = get_current_time();
	for (int i = 0; args.philos_count > i; i++)
		(philos + i)->start_time = start;
	args.start_time = start;
	if (lunch_threads(&threads, philos, args.philos_count, philo_brain) == R_FAIL)
		return (1);
	// for(int i = 0; i < 4; i++)
	// printf("[%p]\n", (philos + i)->locks);
	// the_observer(philos, args);
	wait_threads(threads, args.philos_count);

}