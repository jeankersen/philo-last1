/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvillefr <jvillefr@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:57:11 by jvillefr          #+#    #+#             */
/*   Updated: 2023/07/06 14:02:27 by jvillefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_process(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->table_data->write_mutex);
	printf_status("has taken data fork\n", philo);
	pthread_mutex_unlock(&philo->table_data->write_mutex);
	if (!philo->right_fork)
	{
		ft_usleep(philo->table_data->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->table_data->write_mutex);
	printf_status("has taken data fork\n", philo);
	pthread_mutex_unlock(&philo->table_data->write_mutex);
	pthread_mutex_lock(&philo->table_data->write_mutex);
	printf_status("is eating\n", philo);
	pthread_mutex_lock(&philo->table_data->eat_mutex);
	philo->last_time_eat = timestamp();
	pthread_mutex_unlock(&philo->table_data->eat_mutex);
	pthread_mutex_unlock(&philo->table_data->write_mutex);
	ft_usleep(philo->table_data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	sleep_philo(philo);
	think_philo(philo);
}

void	think_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table_data->write_mutex);
	printf_status("is thinking\n", philo);
	pthread_mutex_unlock(&philo->table_data->write_mutex);
}

void	sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table_data->write_mutex);
	printf_status("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->table_data->write_mutex);
	ft_usleep(philo->table_data->sleep);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = timestamp();
	while ((timestamp() - start_time) < time_in_ms)
		usleep(250);
}

int	ft_exit(char *str)
{
	printf("Error: %s", str);
	return (0);
}
