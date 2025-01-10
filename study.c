# include <stdio.h>
# include <pthread.h>
# include <unistd.h>

int balance = 0;

void write_balance(int new_balance)
{
	usleep(25000); // Simulates a delay in updating the balance
	balance = new_balance;
}

int	read_balance()
{
	usleep(25000); // Simulates a delay in reading the balance
	return balance;
}

typedef	struct {
	int	amount;
	pthread_mutex_t	*mutex;
} ThreadArgs;


void	*deposit(void *args)
{
	ThreadArgs *thread_args = (ThreadArgs *)args;
	int amount = thread_args->amount;
	pthread_mutex_t *mutex = thread_args->mutex;

	pthread_mutex_lock(mutex);
	int account_balance = read_balance();
	account_balance += amount;
	write_balance(account_balance);
	pthread_mutex_unlock(mutex);
	return (NULL);
}

int	main()
{
	int before = read_balance();
	printf("Before: %d\n", before);

	pthread_t thread1;
	pthread_t thread2;
	pthread_mutex_t mutex;

	pthread_mutex_init(&mutex, NULL); // Initialise the mutex

	ThreadArgs args1 = {300, &mutex};
	ThreadArgs args2 = {200, &mutex};

	pthread_create(&thread1, NULL, deposit, (void *) &args1);
	pthread_create(&thread2, NULL, deposit, (void *) &args2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&mutex);

	int after = read_balance();
	printf("After: %d\n", after);

	return 0;
}
