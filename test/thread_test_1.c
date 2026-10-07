#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
typedef struct s_shared
    {
        int			counter;
        pthread_mutex_t counter_mutex;
    }	t_shared;

typedef struct s_coder
    {
        int			id;
        pthread_t	thread;
        t_shared    *ptr;
    }	t_coder;

void	*routine(void *arg)
{
	t_coder     *coder;
    coder = (t_coder *)arg;
    int i = 0;
    while (i < 1000000)
    {
        pthread_mutex_lock(&coder->ptr->counter_mutex);
        coder->ptr->counter++;
        pthread_mutex_unlock(&coder->ptr->counter_mutex);
        i++;
    }
	// printf("thread %d started\n", coder->id);
    // usleep(100000);
	// printf("thread %d done\n", coder->id);
	return (NULL);
}

int	main(void)
{
    t_coder coders[5];
    t_shared    shared;
    shared.counter = 0;
    pthread_mutex_init(&shared.counter_mutex, NULL);

    int i = 0;
    while (i < 5)
    {
        coders[i].id = i + 1;
        coders[i].ptr = &shared;
        pthread_create(&coders[i].thread, NULL, routine, &coders[i]);
        i++;
    }
    i = 0;
    while (i < 5)
    {
        pthread_join(coders[i].thread, NULL);
        i++;
    }
    pthread_mutex_destroy(&shared.counter_mutex);
    printf("counter = %i\n", shared.counter);
	printf("main: thread finished\n");
	return (0);
}