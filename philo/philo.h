/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:26:12 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/01/13 09:18:46 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// printf
# include <stdio.h> 
// usleep
# include <unistd.h>
// gettimeofday
# include <sys/time.h>
// pthread, mutex
# include <pthread.h>
// malloc, free
# include <stdlib.h>
// INT_MAX
# include <limits.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define RESET_COLOR "\033[0m"

# define PHILO_MAX 200

typedef struct s_philo
{
	int				num_of_philo;
	int				id;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				eating;
	int				*dead_flag;
	int				num_of_meals;
	int				eaten;
	long long		last_meal;
	long long		start_time;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dining_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
}	t_philo;

typedef struct s_program
{
	int				num_of_philo;
	int				dead_flag;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dining_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_program;

// utils
int			exit_error(char *msg);
int			philo_atoi(char *str);
int			philo_strcmp(char *s1, char *s2);
int			philo_sleep(long long millisec);
long long	current_time(void);

// check for valid arguments
int			check_args(char **argv);

// initialise all the data into struct	
void		init_program(t_program *program, char **argv);
void		init_philo(t_program *program, char **argv);
void		destroy_mutex(t_program *program);

// dining
int			dead_or_alive(t_philo *philo);
void		*routine(void *args);
void		dining_time(t_program *program);

void		*monitor(void *args);
void		dead(t_philo *philo);
void		satisfied(t_philo *philo);
void		print(char *str, int id, t_philo *philo);

// actions
void		eat(t_philo *philo);
void		sleeping(t_philo *philo);

#endif