/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:19:30 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/01/10 10:24:01 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_philo	*philo;
	int		dead_flag;

	philo = args;
	if (philo->id % 2 == 0)
		philo_sleep(3);
	while (1)
	{
		pthread_mutex_lock(philo->dead_lock);
		dead_flag = *philo->dead_flag;
		pthread_mutex_unlock(philo->dead_lock);
		if (dead_flag == 1)
			break ;
		eat(philo);
		sleeping(philo);
		print("is thinking", philo->id, philo);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	if (philo->num_of_philo == 1)
	{
		philo_sleep(philo->time_to_die);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	print("has taken a fork", philo->id, philo);
	print("has taken a fork", philo->id, philo);
	print("is eating", philo->id, philo);
	pthread_mutex_lock(philo->dining_lock);
	philo->eating = 1;
	philo->last_meal = current_time();
	philo->eaten++;
	philo->eating = 0;
	pthread_mutex_unlock(philo->dining_lock);
	philo_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	print("is sleeping", philo->id, philo);
	philo_sleep(philo->time_to_sleep);
}
