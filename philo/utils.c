/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:37:22 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/01/10 11:35:44 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_error(char *msg)
{
	printf("%s%s%s\n", RED, msg, RESET_COLOR);
	return (1);
}

int	philo_atoi(char *str)
{
	unsigned long	sum;

	sum = 0;
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - '0');
		str++;
	}
	return ((int)sum);
}

int	philo_strcmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while ((s1[++i] != '\0' || s2[i] != '\0'))
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (0);
}

int	philo_sleep(long long millisec)
{
	long long	start;

	start = current_time();
	while (current_time() - start < millisec)
		usleep(500);
	return (0);
}

long long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
