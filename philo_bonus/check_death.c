/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:04:09 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/15 21:11:22 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_philo(t_philo *philo, long current_time)
{
	philo->must_die = e_true;
	sem_wait(philo->data->print_sem);
	printf("%ld %d is dead\n", current_time, philo->id_philo);
	sem_post(philo->data->print_sem);
	sem_post(philo->data->stop_death);
}

void	*check_death(void *p)
{
	t_philo *philo;
	long	current_time;

	philo = (t_philo *)p;
	while (1)
	{
		sem_wait(philo->data->must_die);
		current_time = get_current_time() - philo->data->start_time;
		if (philo->last_eating_time + philo->data->time_to_die < current_time)
		{
			death_philo(philo, current_time);
			break ;
		}
		sem_post(philo->data->must_die);
		sem_wait(philo->data->must_die);
		if (philo->count_eating == 0)
		{
			sem_post(philo->data->stop_death);
			break ;
		}
		sem_post(philo->data->must_die);		
	}
	return (NULL);
}
