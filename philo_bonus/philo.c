/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:18:56 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/13 18:47:43 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_philo *philo, t_global *data)
{
	int i;

	i = 0;
	while (i < data->num_philo)
	{
		kill(philo[i].id_pid, SIGKILL);
		i++;
	}
	sem_close(data->forks);
	sem_close(data->must_die);
	sem_close(data->print_sem);
	sem_close(data->stop_death);
	free(philo);
}

void create_process(t_global *data, t_philo *philo)
{
	int i;
	long start_time;

	i = 0;
	sem_wait(data->stop_death);
	start_time = get_current_time();
	while (i < data->num_philo)
	{
		philo->data->start_time = start_time;
		philo[i].id_pid = fork();
		if (philo[i].id_pid == 0)
			philo_routine(philo + i);
		i++;
		usleep(100);
	}
	sem_wait(data->stop_death);
	destroy_all(philo, data);
}
/* 
int	create_process(t_global *glob, t_philo *philo)
{
	int i;

	i = 0;
	sem_wait(philo[i].semaphors->stop_death);
	while (i < glob->num_philo)
	{
		// printf("%d\n", philo[i].id_philo);
		philo[i].id_pid = fork();
		if (philo[i].id_pid == 0)
			philo_routine(&(philo[i]));
		i++;
	}
	sem_wait(philo[i].semaphors->stop_death);
	int			i;
	pthread_t	*threads_id;
	pthread_t	thread_death;

	threads_id = (pthread_t *)malloc(sizeof(pthread_t) * glob->num_philo);
	i = -1;
	if (pthread_create(&thread_death, NULL, check_death, death_philo))
		return (1);
	while (++i < glob->num_philo)
	{
		if (pthread_create(&(threads_id[i]), NULL,
				philo_routine, &(philo[i])) != 0)
			return (1);
	}
	i = -1;
	if (pthread_join(thread_death, NULL))
		return (1);
	while (++i < glob->num_philo)
	{
		if (pthread_join(threads_id[i], NULL) != 0)
			return (1);
	}
	free(threads_id);
	return (0);
} */

/* void	destroy_all(t_philo *philo, t_global *glob)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(philo->print_mutex);
	while (i < glob->num_philo)
		pthread_mutex_destroy(philo[i++].right_fork->fork);
	free(philo->right_fork->fork);
	free(philo->right_fork);
	free(philo->print_mutex);
	free(philo->must_die);
	free(philo);
} */

int	main(int argc, char **argv)
{
	t_global	data;
	t_philo		*philo;

	parse(argc, argv, &data);
	init_data(&data);
	philo = philo_init(&data);
	create_process(&data, philo);
	/* if (init_philo_forks(&glob, &philo))
		return (ft_exit("Error with initialization\n", 1));
	if (create_process(&glob, philo))
		return (ft_exit("Error with process\n", 1)); */
	// destroy_all(philo, &glob);
}
