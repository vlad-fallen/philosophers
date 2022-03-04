/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:04:09 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/04 21:20:09 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void death_philo(t_philo *philo, long current_time)
{
	*(philo->must_die) = e_true;
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld ms: philo %d is dead\n", current_time, philo->id_philo);
	pthread_mutex_unlock(philo->print_mutex);
}

void *check_death(void *d)
{
	t_death *death;
	int i;
	long current_time;

	death = (t_death *)d;
	while (1)
	{
		i = 0;
		current_time = get_current_time() - death->check_philo[i].start_time;
		while (i < death->num_philo)
		{
			if (death->check_philo[i].last_eating_time + death->check_philo[i].time_to_die < current_time)
			{
				death_philo(&(death->check_philo[i]), current_time);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}