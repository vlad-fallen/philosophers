/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:04:09 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/18 20:22:38 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	death_philo(t_philo *philo, long current_time)
{
	*(philo->must_die) = e_true;
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d is dead\n", current_time, philo->id_philo);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_unlock(philo->right_fork->fork);
	pthread_mutex_unlock(philo->left_fork->fork);
}

void	*check_death(void *d)
{
	t_death	*death;
	int		i;
	long	current_time;
	int		stop_eating;

	death = (t_death *)d;
	while (1)
	{
		i = -1;
		stop_eating = 0;
		current_time = get_current_time() - death->check_philo[0].start_time;
		while (++i < death->num_philo)
		{
			if (death->check_philo[i].count_eating == 0)
				stop_eating++;
			if (death->check_philo[i].last_eating_time
				+ death->check_philo[i].time_to_die < current_time)
			{
				death_philo(&(death->check_philo[i]), current_time);
				return (NULL);
			}
		}
		if (stop_eating >= death->num_philo)
			return (NULL);
	}
}
