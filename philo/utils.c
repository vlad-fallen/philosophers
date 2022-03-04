/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:56:00 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/03 21:00:18 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(char *str, int error)
{
	ft_putstr_fd(str, 2);
	return (error);
}

long get_current_time(void)
{
	struct timeval current_time;
	long	time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void improved_usleep(long time_ms)
{
	long start;
	long current;

	start = get_current_time();
	current = get_current_time();
	while ((current - start) < time_ms)
	{
		usleep(1);
		current = get_current_time();
	}
}