#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct	s_sem
{
	sem_t	*sem;
} t_sem;

void	critical_section(t_sem *resources, int id)
{
	(void)resources;
	printf("Process %d entering critical section.\n", id);
	sleep(1);
	printf("Process %d entering critical section.\n", id);
}

int main()
{
	pid_t	pid;
	int		num_processes = 3;
	int		i;
	t_sem	resources;

	resources.sem = sem_open("/mysem", O_CREAT, 0644, 1);
	if (resources.sem == SEM_FAILED)
	{
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < num_processes)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("Child process %d created\n", i);
			sem_wait(resources.sem);
			critical_section(&resources, i);
			sem_post(resources.sem);
			exit(0);
		}
		else if (pid < 0)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
	}
	i = -1;
	while (++i < num_processes)
		wait(NULL);
	sem_close(resources.sem);
	sem_unlink("/mysem");
}