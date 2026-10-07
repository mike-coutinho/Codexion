#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TOTAL_WORK 2000000000L

typedef struct s_coder
{
	int			id;
	pthread_t	thread;
	long		work;
}	t_coder;

void	*routine(void *arg)
{
	t_coder				*coder;
	volatile long		local;
	long				i;

	coder = (t_coder *)arg;
	local = 0;
	i = 0;
	while (i < coder->work)
	{
		local++;
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_coder	coders[64];
	int		n;
	int		i;

	if (argc != 2)
		return (printf("usage: ./test3 number_of_threads\n"), 1);
	n = atoi(argv[1]);
	if (n < 1 || n > 64)
		return (printf("number_of_threads must be 1..64\n"), 1);
	i = 0;
	while (i < n)
	{
		coders[i].id = i + 1;
		coders[i].work = TOTAL_WORK / n;
		pthread_create(&coders[i].thread, NULL, routine, &coders[i]);
		i++;
	}
	i = 0;
	while (i < n)
	{
		pthread_join(coders[i].thread, NULL);
		i++;
	}
	printf("%d thread(s) done\n", n);
	return (0);
}