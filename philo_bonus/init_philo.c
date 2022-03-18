/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:05:39 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/18 19:07:52 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_global *data)
{
	sem_unlink("forks");
	sem_unlink("must_die");
	sem_unlink("print_sem");
	sem_unlink("stop_death");
	data->forks = sem_open("forks", O_CREAT, 0700, data->num_philo);
	if (data->forks == SEM_FAILED)
		ft_exit("Error with semaphors 1\n", 1);
	data->must_die = sem_open("must_die", O_CREAT, 0700, 1);
	if (data->must_die == SEM_FAILED)
		ft_exit("Error with semaphors 2\n", 1);
	data->print_sem = sem_open("print_sem", O_CREAT, 0700, 1);
	if (data->print_sem == SEM_FAILED)
		ft_exit("Error with semaphors 3\n", 1);
	data->stop_death = sem_open("stop_death", O_CREAT, 0700, 1);
	if (data->stop_death == SEM_FAILED)
		ft_exit("Error with semaphors 4\n", 1);
}

t_philo	*philo_init(t_global *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->num_philo);
	if (!philo)
		ft_exit("Error with allocations\n", 1);
	i = 0;
	while (i < data->num_philo)
	{
		philo[i].id_philo = i;
		philo[i].last_eating_time = 0;
		philo[i].must_die = e_false;
		philo[i].count_eating = data->num_to_eat;
		philo[i].data = data;
		philo[i].id_pid = -1;
		philo[i].current_time = 0;
		i++;
	}
	return (philo);
}
