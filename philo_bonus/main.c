/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:24:58 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/06 13:19:19 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	sem_unlink() is needed at the beginning in case of pressing Ctrl+C
*/
int	main(int argc, char **argv)
{
	t_program	program;
	pid_t		*pid;

	pid = NULL;
	if (argc != 5 && argc != 6)
		exit_error("Incorrect number of arguments.");
	if (check_args(argv))
		return (1);
	init_program(&program, argv);
	run_sim(&program, &pid);
	monitor_children(&program, pid);
	free_all(&program, pid);
	return (0);
}
