/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvillefr <jvillefr@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 07:50:03 by jvillefr          #+#    #+#             */
/*   Updated: 2023/07/06 12:22:31 by jvillefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** libraries
*/

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int						nbr_philo;
	int						time_to_die;
	int						time_to_eat;
	int						sleep;
	int						max_eat;
	long int				start_t;
	pthread_mutex_t			write_mutex;
	pthread_mutex_t			dead_mutex;
	pthread_mutex_t			eat_mutex;
	pthread_mutex_t			finish_mutex;
	int						philo_done;
	int						stop;
}							t_data;

typedef struct s_philo
{
	int						id;
	pthread_t				thread_id;
	pthread_t				thread_death_id;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			left_fork;
	t_data					*table_data;
	long int				last_time_eat;
	unsigned int			eat_time;
	int						done;
}							t_philo;

typedef struct s_table
{
	t_philo					*philo;
	t_data					data;
}							t_table;

long int		timestamp(void);
int				ft_exit(char *str);
int				ft_strlen(char *str);
void			*is_dead(void	*data);
int				ft_atoi(const char *str);
void			*thread_philo(void *data);
int				str_only_digit(char *str);
int				init_table(t_table *table);
void			think_philo(t_philo *philo);
void			sleep_philo(t_philo *philo);
int				start_thread(t_table *table);
void			ft_putstr_fd(char *s, int fd);
void			philo_process(t_philo *philo);
void			ft_usleep(long int time_in_ms);
int				check_args(int argc, char **argv);
int				check_death(t_philo *philo, int i);
int				parse_args(char **argv, t_table *table);
void			printf_status(char *str, t_philo *philo);
#endif
