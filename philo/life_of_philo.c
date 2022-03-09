/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:15:03 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/08 19:11:56 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork->fork);
	pthread_mutex_unlock(philo->right_fork->fork);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork->fork);
	if (*(philo->must_die) == e_true)
	{
		put_down_forks(philo);
		return ;
	}
	philo->right_fork->use = e_true;
	philo->right_fork->ph_id = philo->id_philo;
	print_message(philo, "has taken right fork");
	pthread_mutex_lock(philo->left_fork->fork);
	if (*(philo->must_die) == e_true)
	{
		put_down_forks(philo);
		return ;
	}
	philo->left_fork->use = e_true;
	philo->left_fork->ph_id = philo->id_philo;
	print_message(philo, "has taken left fork");
}

static void	philo_eating(t_philo *philo)
{
	if (philo->left_fork->ph_id != philo->id_philo
		&& philo->right_fork->ph_id != philo->id_philo)
		return ;
	print_message(philo, "is eating");
	improved_usleep(philo->time_to_eat);
	if (philo->count_eating != -1)
		philo->count_eating--;
	pthread_mutex_unlock(philo->right_fork->fork);
	philo->right_fork->use = e_false;
	philo->right_fork->ph_id = -1;
	pthread_mutex_unlock(philo->left_fork->fork);
	philo->left_fork->use = e_false;
	philo->left_fork->ph_id = -1;
	philo->last_eating_time = get_current_time() - philo->start_time;
}

static void	philo_sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	improved_usleep(philo->time_to_sleep);
}

void	*philo_routine(void *p)
{
	t_philo	*philo_data;

	philo_data = (t_philo *)p;
	if (philo_data->id_philo % 2 == 1)
		usleep(2500);
	while (1)
	{
		print_message(philo_data, "is thinking");
		if (*(philo_data->must_die) == e_true)
			break ;
		take_forks(philo_data);
		if (*(philo_data->must_die) == e_true)
			break ;
		philo_eating(philo_data);
		if (philo_data->count_eating == 0)
			break ;
		if (*(philo_data->must_die) == e_true)
			break ;
		philo_sleeping(philo_data);
		if (*(philo_data->must_die) == e_true)
			break ;
	}
	return (NULL);
}
