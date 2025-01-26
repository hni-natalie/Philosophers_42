/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:53:51 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/01/26 17:29:01 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*dining_time(t_philo *philo)
{
	pthread_t	monitor_philo;	

	if (pthread_create(&monitor_philo, NULL, monitor, philo) != 0)
		return ((void *)-1);
	if (pthread_detach(monitor_philo) != 0)
		return ((void *)-1);
	if (philo->id % 2 == 0)
		philo_sleep(3);
	while (1)
	{
		if (philo->program->num_of_philo == 1)
			philo_sleep(philo->program->time_to_die);
		eat(philo);
		if (philo->eaten == philo->program->num_of_meals)
			exit(0);
		print("is sleeping", philo->id, philo->program);
		philo_sleep(philo->program->time_to_sleep);
		print("is thinking", philo->id, philo->program);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->program->forks);
	sem_wait(philo->program->forks);
	sem_wait(philo->program->eat_lock);
	print("has taken a fork", philo->id, philo->program);
	print("has taken a fork", philo->id, philo->program);
	print("is eating", philo->id, philo->program);
	philo->last_meal = current_time();
	philo->eaten++;
	sem_post(philo->program->eat_lock);
	philo_sleep(philo->program->time_to_eat);
	sem_post(philo->program->forks);
	sem_post(philo->program->forks);
}

void	*monitor(void *args)
{
	t_philo	*philo;
	int		time;

	philo = args;
	while (1)
	{
		if (current_time() - philo->last_meal >= philo->program->time_to_die)
		{
			sem_wait(philo->program->print_lock);
			time = current_time() - philo->program->start_time;
			printf("%s%d %d %s%s\n", RED, time, philo->id, "died", RESET_COLOR);
			exit(1);
		}
	}
	return (NULL);
}

void	print(char *str, int id, t_program *program)
{
	int	time;

	sem_wait(program->print_lock);
	time = current_time() - program->start_time;
	if (philo_strcmp(str, "is eating") == 0)
		printf("%s%d %d %s%s\n", GREEN, time, id, str, RESET_COLOR);
	else
		printf("%d %d %s\n", time, id, str);
	sem_post(program->print_lock);
}
