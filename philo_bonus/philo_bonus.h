/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:26:12 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/04 14:55:38 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// printf
# include <stdio.h> 
// usleep, fork 
# include <unistd.h>
// gettimeofday
# include <sys/time.h>
// waitpid
# include <sys/wait.h>
// semaphore
# include <semaphore.h>
// malloc, free
# include <stdlib.h>
// INT_MAX
# include <limits.h>
// mode 
# include <fcntl.h>
// pthread 
# include <pthread.h>
// SIGTERM
# include <signal.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define RESET_COLOR "\033[0m"

# define PHILO_MAX 200

typedef struct s_philo	t_philo;

typedef struct s_program
{
	t_philo		*philo;
	int			num_of_philo;
	int			time_to_die;
	int			time_to_sleep;
	int			time_to_eat;
	int			num_of_meals;
	long long	start_time;
	sem_t		*forks;
	sem_t		*print_lock;
	sem_t		*eat_lock;
}	t_program;

typedef struct s_philo
{
	int					id;
	_Atomic int			eaten;
	_Atomic long long	last_meal;
	t_program			*program;
}	t_philo;

// check for valid arguments
int			check_args(char **argv);
void		monitor_children(t_program *program, pid_t *pid);
void		free_all(t_program *program, pid_t *pid);
void		run_sim(t_program *program, pid_t **pid);

// init
void		init_program(t_program *program, char **argv);

// dining
void		*dining_time(t_philo *philo);
void		eat(t_philo *philo);
void		*monitor(void *args);
void		print(char *str, int id, t_program *program);

// utils
void		exit_error(char *msg);
int			philo_atoi(char *str);
int			philo_strcmp(char *s1, char *s2);
long long	current_time(void);
int			philo_sleep(long long millisec);

#endif
