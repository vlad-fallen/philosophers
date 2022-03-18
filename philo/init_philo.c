/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:05:39 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/18 20:22:43 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	forks_init(t_fork **forks_out, t_global *glob)
{
	int				i;
	t_fork			*forks;
	pthread_mutex_t	*fork_mutex;

	forks = (t_fork *)malloc(sizeof(t_fork) * glob->num_philo);
	fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
					glob->num_philo);
	if (!forks || !fork_mutex)
		return (1);
	i = 0;
	while (i < glob->num_philo)
	{
		forks[i].fork_id = i;
		forks[i].use = e_false;
		forks[i].ph_id = -1;
		pthread_mutex_init(fork_mutex + i, NULL);
		forks[i].fork = fork_mutex + i;
		i++;
	}
	*forks_out = forks;
	return (0);
}

static int	philo_init(t_philo **philo_out, t_global *glob, t_fork *forks)
{
	int		i;
	t_philo	*philo;
	long	current_time;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * glob->num_philo);
	if (!philo)
		return (1);
	current_time = get_current_time();
	while (++i < glob->num_philo)
	{
		philo[i].time_to_die = glob->time_to_die;
		philo[i].time_to_eat = glob->time_to_eat;
		philo[i].time_to_sleep = glob->time_to_sleep;
		philo[i].id_philo = i;
		philo[i].last_eating_time = 0;
		philo[i].right_fork = forks + i;
		philo[i].left_fork = forks + (i + 1) % glob->num_philo;
		philo[i].start_time = current_time;
		philo[i].count_eating = glob->num_to_eat;
	}
	*philo_out = philo;
	return (0);
}

int	init_philo_forks(t_global *glob, t_philo **philo_out, t_death *death_philo)
{
	int				i;
	t_philo			*philo;
	t_fork			*forks;
	t_bool			*death;
	pthread_mutex_t	*print_m;

	print_m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	death = (t_bool *)malloc(sizeof(t_bool));
	if (forks_init(&forks, glob) || philo_init(&philo, glob, forks)
		|| !print_m || !death)
		return (1);
	i = -1;
	pthread_mutex_init(print_m, NULL);
	*death = e_false;
	while (++i < glob->num_philo)
	{
		philo[i].must_die = death;
		philo[i].print_mutex = print_m;
		philo[i].current_time = 0;
	}
	*philo_out = philo;
	death_philo->check_philo = philo;
	death_philo->death = death;
	death_philo->num_philo = glob->num_philo;
	return (0);
}
