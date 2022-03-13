/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:05:39 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/13 18:38:30 by mbutter          ###   ########.fr       */
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
	data->current_time = 0;
	// data->start_time = get_current_time();
}

t_philo	*philo_init(t_global *data)
{
	t_philo *philo;
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
		i++;
	}
	return (philo);
}

/* int	forks_init(t_fork **forks_out, t_global *glob)
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
} */
/* 
int semaphor_init(t_sem **sem_out, int num_philo)
{
	t_sem *sem;

	sem = (t_sem *)malloc(sizeof(t_sem));
	if (!sem)
		return (1);
	sem_unlink("forks");
	sem_unlink("must_die");
	sem_unlink("print_sem");
	sem_unlink("stop_death");
	sem->forks = sem_open("forks", O_CREAT, num_philo);
	sem->must_die = sem_open("must_die", O_CREAT, num_philo);
	sem->print_sem = sem_open("print_sem", O_CREAT, num_philo);
	sem->stop_death = sem_open("stop_death", O_CREAT, num_philo);
	*(sem_out) = sem;
	return (0);
}



int	init_philo_forks(t_global *glob, t_philo **philo_out)
{
	t_philo	*philo;

	if (philo_init(&philo, glob))
		return (1);
	*philo_out = philo;
	return (0);
}
 */