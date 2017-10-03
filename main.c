#include "includes/malloc.h"

void	*allocate()
{
	int		i;
	char 	*str;

	i = 0;
	while (i < 100)
	{
		str = malloc(420);
		str[0] = 42;
		i++;
	}
	show_alloc_mem();
	
	return (NULL);
}

int 	main()
{
	int			i;
	pthread_t	thread_id;

	i = 0;
	while (i < 10)
	{
		if (pthread_create(&thread_id, NULL, allocate, NULL) != 0)
		{
			printf("Error on thread creation\n");
			exit(1);
		}
		i++;
	}
	sleep(1);
	show_alloc_mem();
	return (0);
}