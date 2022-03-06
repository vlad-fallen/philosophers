/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:34:20 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/06 17:43:50 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	long	current_time;

	pthread_mutex_lock(philo->print_mutex);
	current_time = get_current_time();
	philo->current_time = current_time - philo->start_time;
	if (*(philo->must_die) == e_true)
	{
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	printf("%ld %d %s\n", philo->current_time, philo->id_philo, message);
	pthread_mutex_unlock(philo->print_mutex);
}
