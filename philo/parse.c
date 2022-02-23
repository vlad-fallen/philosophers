/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:24:10 by mbutter           #+#    #+#             */
/*   Updated: 2022/02/23 14:27:30 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int simple_atoi(char *str)
{
	unsigned int	i;
	unsigned long	n;

	i = 0;
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	return ((int)n);
}

int check_arg(char **argv, int argc)
{
	int i;
	int j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse(int argc, char **argv, t_global *a)
{
	if (check_arg(argv, argc))
		return (1);
	if (argc == 5 || argc == 6)
	{
		a->num_philo = simple_atoi(argv[1]);
		a->time_to_die = simple_atoi(argv[2]) * 1000;
		a->time_to_eat = simple_atoi(argv[3]) * 1000;
		a->time_to_sleep = simple_atoi(argv[4]) * 1000;
		a->num_to_eat = -1;
		if (argc == 6)
			a->num_to_eat = simple_atoi(argv[5]);
	}
	if (a->num_philo == 0 || a->time_to_die == 0 || a->time_to_eat == 0 || a->time_to_sleep == 0 || a->num_to_eat == 0)
		return (1);
	return (0);
}