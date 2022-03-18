/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:18:56 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/18 20:19:56 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_all(t_philo *philo, t_global *data)
{
	usleep(data->time_to_die * 1000);
	sem_close(data->forks);
	sem_close(data->must_die);
	sem_close(data->print_sem);
	sem_close(data->stop_death);
	sem_unlink("forks");
	sem_unlink("must_die");
	sem_unlink("print_sem");
	sem_unlink("stop_death");
	free(philo);
}

void	create_process(t_global *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		philo[i].id_pid = fork();
		if (philo[i].id_pid == 0)
		{
			philo_routine(philo + i);
			exit(0);
		}
		i++;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	t_global	data;
	t_philo		*philo;

	parse(argc, argv, &data);
	init_data(&data);
	philo = philo_init(&data);
	data.start_time = get_current_time();
	sem_wait(data.stop_death);
	create_process(&data, philo);
	sem_wait(data.stop_death);
	destroy_all(philo, &data);
	exit(0);
}
