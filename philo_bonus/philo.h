/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:20:10 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/17 20:50:34 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef enum e_bool
{
	e_false,
	e_true
}	t_bool;

typedef struct s_global
{
	int		num_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_to_eat;
	long	start_time;
	sem_t	*forks;
	sem_t	*must_die;
	sem_t	*print_sem;
	sem_t	*stop_death;
}	t_global;

typedef struct s_philo
{
	pid_t		id_pid;
	int			id_philo;
	int			last_eating_time;
	int			count_eating;
	long		current_time;
	t_bool		must_die;
	t_global	*data;
}	t_philo;

void	parse(int argc, char **argv, t_global *a);
void	init_data(t_global *data);
t_philo	*philo_init(t_global *data);
void	philo_routine(t_philo *philo);
void	*check_death(void *p);
void	destroy_all(t_philo *philo, t_global *data);

/* utils */
void	ft_exit(char *str, int error);
long	get_current_time(void);
void	improved_usleep(long time_ms);
void	ft_putstr_fd(char *s, int fd);
void	print_message(t_philo *philo, char *message);

#endif