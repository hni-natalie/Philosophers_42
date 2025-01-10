/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:24:58 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/01/10 11:35:32 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc != 5 && argc != 6)
		return (exit_error("Incorrect number of arguments."));
	if (check_args(argv))
		return (1);
	init_program(&program, argv);
	init_philo(&program, argv);
	dining_time(&program);
	destroy_mutex(&program);
	free(program.philo);
	free(program.fork);
	return (0);
}

int	check_args(char **argv)
{
	int	i;
	int	j;
	int	num;

	i = 0;
	while (argv[++i])
	{
		if (!argv[i] || !*argv[i])
			return (exit_error("Invalid Argument."));
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (exit_error("Argument Must be Positive Integer."));
		num = philo_atoi(argv[i]);
		if (i == 1 && num > PHILO_MAX)
			return (exit_error("Number of philo must be within 1 to 200."));
		if ((i >= 2 && i <= 4) && num < 60)
			return (exit_error("Time must be at least 60 ms."));
		if (i == 5 && num < 1)
			return (exit_error("Last argument must be at least 1."));
	}
	return (0);
}

void	init_program(t_program *program, char **argv)
{
	int	i;

	i = -1;
	program->num_of_philo = philo_atoi(argv[1]);
	program->dead_flag = 0;
	program->philo = malloc(sizeof(t_philo) * program->num_of_philo);
	program->fork = malloc(sizeof(pthread_mutex_t) * program->num_of_philo);
	if (!program->philo || !program->fork)
		return ;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->dining_lock, NULL);
	pthread_mutex_init(&program->print_lock, NULL);
	while (++i < program->num_of_philo)
		pthread_mutex_init(&program->fork[i], NULL);
}

void	init_philo(t_program *program, char **argv)
{
	int	i;

	i = -1;
	while (++i < program->num_of_philo)
	{
		program->philo[i].num_of_philo = program->num_of_philo;
		program->philo[i].time_to_die = philo_atoi(argv[2]);
		program->philo[i].time_to_eat = philo_atoi(argv[3]);
		program->philo[i].time_to_sleep = philo_atoi(argv[4]);
		program->philo[i].num_of_meals = -1;
		if (argv[5])
			program->philo[i].num_of_meals = philo_atoi(argv[5]);
		program->philo[i].id = i + 1;
		program->philo[i].eating = 0;
		program->philo[i].eaten = 0;
		program->philo[i].start_time = current_time();
		program->philo[i].last_meal = current_time();
		program->philo[i].dead_flag = &program->dead_flag;
		program->philo[i].dead_lock = &program->dead_lock;
		program->philo[i].dining_lock = &program->dining_lock;
		program->philo[i].print_lock = &program->print_lock;
		program->philo[i].left_fork = &program->fork[i];
		program->philo[i].right_fork = &program->fork[(i + 1)
			% program->num_of_philo];
	}
}

void	destroy_mutex(t_program *program)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->dining_lock);
	pthread_mutex_destroy(&program->print_lock);
	while (++i < program->num_of_philo)
		pthread_mutex_destroy(&program->fork[i]);
}
