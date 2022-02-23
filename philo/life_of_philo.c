/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:15:03 by mbutter           #+#    #+#             */
/*   Updated: 2022/02/23 16:40:08 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *p)
{
	t_philo *philo_data;

	philo_data = (t_philo *)p;
	if (philo_data->id_philo % 2 == 1)
		usleep(2500);
/*	while(1)
	{
		
	}*/
	printf("philo %d\n", philo_data->id_philo);
	return (NULL);
}