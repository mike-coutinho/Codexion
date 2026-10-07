#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_coder
    {
        int			id;
        pthread_t	thread;
    }	t_coder;
    
void	*routine(void *arg)
{
	t_coder     *coder;
    coder = (t_coder *)arg;
	printf("thread %d started\n", coder->id);
    usleep(100000);
	printf("thread %d done\n", coder->id);
	return (NULL);
}

int	main(void)
{
    t_coder coders[5];
    int i = 0;
    while (i < 5)
    {
        coders[i].id = i + 1;
        pthread_create(&coders[i].thread, NULL, routine, &coders[i]);
        i++;
    }
    i = 0;
    while (i < 5)
    {
        pthread_join(coders[i].thread, NULL);
        i++;
    }
	printf("main: thread finished\n");
	return (0);
}