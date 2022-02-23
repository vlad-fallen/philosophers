/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:05:39 by mbutter           #+#    #+#             */
/*   Updated: 2022/02/23 15:06:50 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_philo_forks(t_global *glob, t_philo **philo_out)
{
	int i;
	t_philo *philo;
	t_fork *forks;
	pthread_mutex_t *fork_mutex;

	philo = (t_philo *)malloc(sizeof(t_philo) * glob->num_philo);
	forks = (t_fork *)malloc(sizeof(t_fork) * glob->num_philo);
	fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * glob->num_philo);
	if (!philo || !forks || !fork_mutex)
		return (1);
	i = 0;
	while (i < glob->num_philo)
	{
		forks[i].fork_id = i;
		forks[i].use = e_false;
		pthread_mutex_init(fork_mutex + i, NULL);
		forks[i].fork = fork_mutex + i;
		i++;
	}
	i = 0;
	while (i < glob->num_philo)
	{
		philo[i].time_to_die = glob->time_to_die;
		philo[i].time_to_eat = glob->time_to_eat;
		philo[i].time_to_sleep = glob->time_to_sleep;
		philo[i].id_philo = i;
		philo[i].last_eating_time = 0;
		philo[i].must_die = e_false;
		philo[i].right_fork = forks + i;
		philo[i].left_fork = forks + (i + 1) % glob->num_philo;
		i++;
	}
	*philo_out = philo;
	return (0);
}