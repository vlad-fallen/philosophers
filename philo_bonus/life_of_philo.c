/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:15:03 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/13 18:27:42 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_message(philo, "has taken right fork");
	sem_wait(philo->data->forks);
	print_message(philo, "has taken left fork");
}

void	philo_eating(t_philo *philo)
{
	print_message(philo, "is eating");
	improved_usleep(philo->data->time_to_eat);
	if (philo->count_eating != -1)
		philo->count_eating--;
	philo->last_eating_time = get_current_time() - philo->data->start_time;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	philo_sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	improved_usleep(philo->data->time_to_sleep);
}

void	philo_routine(t_philo *philo)
{
	pthread_t thread_death;

	if (pthread_create(&thread_death, NULL, check_death, philo))
		ft_exit("Error with thread", 1);
	if (philo->id_philo % 2 == 1)
		usleep(2500);
	while (1)
	{
		print_message(philo, "is thinking");
		take_forks(philo);
		if (philo->must_die == e_true)
			break ;
		philo_eating(philo);
		if (philo->must_die == e_true)
			break ;
		philo_sleeping(philo);
		if (philo->must_die == e_true)
			break ;
	}
	if (pthread_join(thread_death, NULL))
		ft_exit("Error with thread", 1);
	sem_post(philo->data->stop_death);
	exit(0);
}

/* void	put_down_forks(t_philo *philo)
{
	
} */

/* void	take_forks(t_philo *philo)
{
	sem_wait(philo->semaphors->forks);
	print_message(philo, "has taken right fork");
	sem_wait(philo->semaphors->forks);
	print_message(philo, "has taken left fork");
}

void	philo_eating(t_philo *philo)
{
	print_message(philo, "is eating");
	improved_usleep(philo->time_to_eat);
	sem_post(philo->semaphors->forks);
	sem_post(philo->semaphors->forks);
}

void	philo_sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	improved_usleep(philo->time_to_sleep);
}

void	philo_routine(t_philo *philo)
{
	if (philo->id_philo % 2 == 1)
		usleep(2500);
	
	while (1)
	{
		//print_message(philo, "is thinking");
		// if (*(philo_data->must_die) == e_true)
		// 	break ;
		take_forks(philo);
		// if (*(philo_data->must_die) == e_true)
		// 	break ;
		philo_eating(philo);
		// if (philo_data->count_eating == 0)
		// 	break ;
		// if (*(philo_data->must_die) == e_true)
		// 	break ;
		philo_sleeping(philo);
		// if (*(philo_data->must_die) == e_true)
		break ;
	}
	exit(0);
}
 */