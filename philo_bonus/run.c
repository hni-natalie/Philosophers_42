/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:33:58 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/04 17:04:18 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_args(char **argv)
{
	int	i;
	int	j;
	int	num;

	i = 0;
	while (argv[++i])
	{
		if (!argv[i] || !*argv[i])
			exit_error("Invalid Argument.");
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				exit_error("Argument Must be Positive Integer.");
		num = philo_atoi(argv[i]);
		if (i == 1 && num > PHILO_MAX)
			exit_error("Number of philo must be within 1 to 200.");
		if ((i >= 2 && i <= 4) && num < 60)
			exit_error("Time must be at least 60 ms.");
		if (i == 5 && num < 1)
			exit_error("Last argument must be at least 1.");
	}
	return (0);
}

void	init_program(t_program *program, char **argv)
{
	int	i;

	i = -1;
	program->num_of_philo = philo_atoi(argv[1]);
	program->time_to_die = philo_atoi(argv[2]);
	program->time_to_eat = philo_atoi(argv[3]);
	program->time_to_sleep = philo_atoi(argv[4]);
	program->num_of_meals = -1;
	if (argv[5])
		program->num_of_meals = philo_atoi(argv[5]);
	program->philo = malloc(sizeof(t_philo) * program->num_of_philo);
	if (!program->philo)
		exit_error("Malloc Error.");
	program->start_time = current_time() + (program->num_of_philo * 60);
	program->forks = sem_open("forks", O_CREAT, 0644, program->num_of_philo);
	program->print_lock = sem_open("print_lock", O_CREAT, 0644, 1);
	program->eat_lock = sem_open("eat_lock", O_CREAT, 0644, 1);
	while (++i < program->num_of_philo)
	{
		program->philo[i].id = i + 1;
		program->philo[i].eaten = 0;
		program->philo[i].last_meal = program->start_time;
		program->philo[i].program = program;
	}
}

void	run_sim(t_program *program, pid_t **pid)
{
	int		i;
	pid_t	philo_pid;

	i = -1;
	*pid = malloc(sizeof(pid_t) * program->num_of_philo);
	if (!*pid)
		exit_error("Malloc Error.");
	while (++i < program->num_of_philo)
	{
		philo_pid = fork();
		if (philo_pid == 0)
			dining_time(&program->philo[i]);
		else if (philo_pid > 0)
			(*pid)[i] = philo_pid;
		else
		{
			free_all(program, *pid);
			exit_error("Fork Error.");
		}
	}
}

/*
	first while loop is to wait for any child process and 
		check the status of the children
	second while loop is to wait for the children to finish
*/
void	monitor_children(t_program *program, pid_t *pid)
{
	int	i;
	int	status;

	i = -1;
	while (++i < program->num_of_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < program->num_of_philo)
				kill(pid[i], SIGKILL);
			break ;
		}
	}
	i = -1;
	while (++i < program->num_of_philo)
		waitpid(pid[i], NULL, 0);
}

void	free_all(t_program *program, pid_t *pid)
{
	if (program)
	{
		if (program->philo)
			free(program->philo);
		if (program->forks)
			sem_close(program->forks);
		if (program->print_lock)
			sem_close(program->print_lock);
		if (program->eat_lock)
			sem_close(program->eat_lock);
		sem_unlink("forks");
		sem_unlink("print_lock");
		sem_unlink("eat_lock");
	}
	if (pid)
		free(pid);
}
