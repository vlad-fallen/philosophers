/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:18:56 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/08 19:13:12 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_global *glob, t_philo *philo, t_death *death_philo)
{
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
}

static void	destroy_all(t_philo *philo, t_global *glob)
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
}

int	main(int argc, char **argv)
{
	t_global	glob;
	t_death		death_philo;
	t_philo		*philo;

	if (parse(argc, argv, &glob))
		return (ft_exit("Error with arguments\n", 1));
	if (init_philo_forks(&glob, &philo, &death_philo))
		return (ft_exit("Error with initialization\n", 1));
	if (create_threads(&glob, philo, &death_philo))
		return (ft_exit("Error with threads\n", 1));
	destroy_all(philo, &glob);
}
