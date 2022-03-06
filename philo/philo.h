/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:20:10 by mbutter           #+#    #+#             */
/*   Updated: 2022/03/06 17:43:34 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_bool
{
	e_false,
	e_true
}	t_bool;

typedef struct s_fork
{
	pthread_mutex_t	*fork;
	int				fork_id;
	int				ph_id;
	t_bool			use;
}	t_fork;

typedef struct s_philo
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				id_philo;
	pthread_t		id_thread;
	t_fork			*right_fork;
	t_fork			*left_fork;
	int				last_eating_time;
	t_bool			*must_die;
	int				count_eating;
	pthread_mutex_t	*print_mutex;
	long			start_time;
	long			current_time;
}	t_philo;

typedef struct s_global
{
	int		num_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_to_eat;
}	t_global;

typedef struct s_death
{
	t_philo	*check_philo;
	t_bool	*death;
	int		num_philo;
}	t_death;

int		parse(int argc, char **argv, t_global *a);
int		init_philo_forks(t_global *glob, t_philo **philo, t_death *philo_death);
void	*philo_routine(void *p);
void	*check_death(void *g);

/* print_message */
void	print_message(t_philo *philo, char *message);

/* utils */
int		ft_exit(char *str, int error);
long	get_current_time(void);
void	improved_usleep(long time_ms);

/* lib_func */
void	ft_putstr_fd(char *s, int fd);

#endif