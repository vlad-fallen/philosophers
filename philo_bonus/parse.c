/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:24:10 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/16 20:50:45 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	simple_atoi(char *str)
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

static int	check_arg(char **argv, int argc)
{
	int	i;
	int	j;

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

void	parse(int argc, char **argv, t_global *data)
{
	if (check_arg(argv, argc))
		ft_exit("Error with argument\n", 1);
	if (argc == 5 || argc == 6)
	{
		data->num_philo = simple_atoi(argv[1]);
		data->time_to_die = simple_atoi(argv[2]);
		data->time_to_eat = simple_atoi(argv[3]);
		data->time_to_sleep = simple_atoi(argv[4]);
		data->num_to_eat = -1;
		if (argc == 6)
			data->num_to_eat = simple_atoi(argv[5]);

	}
	else 
		ft_exit("Error with argument\n", 1);
	if (data->num_philo == 0 || data->time_to_die == 0 || data->time_to_eat == 0
		|| data->time_to_sleep == 0 || data->num_to_eat == 0)
	{
		ft_exit("Error with argument\n", 1);
	}
}
