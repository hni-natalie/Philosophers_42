/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:54:21 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/04 10:43:53 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dining_time(t_program *program)
{
	pthread_t	monitor_philo;
	int			i;

	i = -1;
	if (pthread_create(&monitor_philo, NULL, monitor, program->philo) != 0)
		destroy_mutex(program);
	while (++i < program->num_of_philo)
		if (pthread_create(&program->philo[i].thread, NULL,
				routine, &program->philo[i]) != 0)
			destroy_mutex(program);
	if (pthread_join(monitor_philo, NULL) != 0)
		destroy_mutex(program);
	i = -1;
	while (++i < program->num_of_philo)
		if (pthread_join(program->philo[i].thread, NULL) != 0)
			destroy_mutex(program);
}

/**
 * @brief This function is used to monitor the philo's status
 * @param args the philo struct
 * 
 * This function will monitor the philo's status
 * If the philo is dead or satisfied, it will break the loop
 * @return void*
 */
void	*monitor(void *args)
{
	t_philo	*philo;
	int		dead_flag;

	philo = args;
	while (1)
	{
		dead(philo);
		satisfied(philo);
		pthread_mutex_lock(philo->dead_lock);
		dead_flag = *philo->dead_flag;
		pthread_mutex_unlock(philo->dead_lock);
		if (dead_flag == 1)
			break ;
	}
	return (NULL);
}

void	dead(t_philo *philo)
{
	int		i;
	int		eating;

	i = -1;
	while (++i < philo->num_of_philo)
	{
		pthread_mutex_lock(philo->dining_lock);
		eating = philo->eating;
		pthread_mutex_unlock(philo->dining_lock);
		if (current_time() - philo[i].last_meal >= philo[i].time_to_die
			&& eating == 0)
		{
			print("died", philo[i].id, &philo[i]);
			pthread_mutex_lock(philo->dead_lock);
			*philo->dead_flag = 1;
			pthread_mutex_unlock(philo->dead_lock);
		}
	}
}

void	satisfied(t_philo *philo)
{
	int	full;
	int	i;

	full = 0;
	i = -1;
	if (philo->num_of_meals == -1)
		return ;
	while (++i < philo->num_of_philo)
		if (philo[i].eaten >= philo->num_of_meals)
			full += 1;
	if (full == philo->num_of_philo)
	{
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead_flag = 1;
		pthread_mutex_unlock(philo->dead_lock);
	}
}

void	print(char *str, int id, t_philo *philo)
{
	int	time;
	int	dead_flag;

	time = current_time() - philo->start_time;
	pthread_mutex_lock(philo->dead_lock);
	dead_flag = *philo->dead_flag;
	pthread_mutex_unlock(philo->dead_lock);
	if (dead_flag == 0)
	{
		pthread_mutex_lock(philo->print_lock);
		if (philo_strcmp(str, "is eating") == 0)
			printf("%s%d %d %s%s\n", GREEN, time, id, str, RESET_COLOR);
		else
			printf("%d %d %s\n", time, id, str);
		pthread_mutex_unlock(philo->print_lock);
	}
}
