#include "philo.h"

// void print_args(t_philosopher args)
// {
//     printf("%ld\n", args.philos_count);
//     printf("%ld\n", args.time_to_die);
//     printf("%ld\n", args.time_to_eat);
//     printf("%ld\n", args.time_to_sleep);
//     printf("%ld\n", args.num_times_must_eat);
// }

void print_table(t_philosopher *philos, int count)
{
	int i;

	i = -1;
	while (++i < count)
	{
		// printf("i = %d\n", i);
		// printf("id: %d \n", philos[i].id);
		printf("LF: %p | RF: %p\n", &philos[i].left_fork, &philos[i].right_fork);
	}
}