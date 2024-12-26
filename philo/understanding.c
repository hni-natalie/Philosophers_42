# include <stdio.h>
# include <pthread.h>

void	*computation()
{
	printf("Computation\n");
	return NULL;
}

int main()
{
	pthread_t thread1;

	pthread_create(&thread1, NULL, computation, NULL);
	pthread_join(thread1, NULL); 
	// pthread_join() waits for the thread to finish execution
	// NULL means that the program does not care about the return value of the thread that is being joined
	return (0);
}