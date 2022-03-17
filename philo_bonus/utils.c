/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:56:00 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/17 20:52:25 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(char *str, int error)
{
	ft_putstr_fd(str, 2);
	exit(error);
}

long	get_current_time(void)
{
	struct timeval	current_time;
	long			time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	improved_usleep(long time_ms)
{
	long	start;
	long	current;

	start = get_current_time();
	current = get_current_time();
	while ((current - start) < time_ms)
	{
		usleep(10);
		current = get_current_time();
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

void	print_message(t_philo *philo, char *message)
{
	long	current_time;

	sem_wait(philo->data->print_sem);
	current_time = get_current_time();
	philo->current_time = current_time - philo->data->start_time;
	if (philo->must_die == e_true)
	{
		sem_post(philo->data->print_sem);
		return ;
	}
	printf("%ld %d %s\n", philo->current_time, philo->id_philo, message);
	sem_post(philo->data->print_sem);
}
