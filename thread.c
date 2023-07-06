/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvillefr <jvillefr@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:57:27 by jvillefr          #+#    #+#             */
/*   Updated: 2023/07/06 13:43:55 by jvillefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	start_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data.nbr_philo)
	{
		table->philo[i].table_data = &table->data;
		if (pthread_create(&table->philo[i].thread_id, NULL, \
			thread_philo, &table->philo[i]) != 0)
			return (ft_exit("Pthread failed\n"));
		i++;
	}
	return (1);
}

void	*thread_philo(void *data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->table_data->time_to_eat / 10);
	while (!check_death(philo, 0))
	{
		pthread_create(&philo->thread_death_id, NULL, is_dead, data);
		philo_process(philo);
		if ((int)++philo->eat_time == philo->table_data->max_eat)
		{
			pthread_mutex_lock(&philo->table_data->finish_mutex);
			philo->done = 1;
			philo->table_data->philo_done++;
			if (philo->table_data->philo_done == philo->table_data->nbr_philo)
			{
				pthread_mutex_unlock(&philo->table_data->finish_mutex);
				check_death(philo, 2);
			}
			pthread_mutex_unlock(&philo->table_data->finish_mutex);
			return (NULL);
		}
	}
	return (NULL);
}

int	check_death(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->table_data->dead_mutex);
	if (i)
		philo->table_data->stop = i;
	if (philo->table_data->stop)
	{
		pthread_mutex_unlock(&philo->table_data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table_data->dead_mutex);
	return (0);
}

void	*is_dead(void	*data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	ft_usleep(philo->table_data->time_to_die + 1);
	pthread_mutex_lock(&philo->table_data->eat_mutex);
	pthread_mutex_lock(&philo->table_data->finish_mutex);
	if (!check_death(philo, 0) && !philo->done && \
	((timestamp() - philo->last_time_eat) \
	>= (long)(philo->table_data->time_to_die)))
	{
		pthread_mutex_unlock(&philo->table_data->eat_mutex);
		pthread_mutex_unlock(&philo->table_data->finish_mutex);
		pthread_mutex_lock(&philo->table_data->write_mutex);
		printf_status("died\n", philo);
		pthread_mutex_unlock(&philo->table_data->write_mutex);
		check_death(philo, 1);
	}
	pthread_mutex_unlock(&philo->table_data->eat_mutex);
	pthread_mutex_unlock(&philo->table_data->finish_mutex);
	return (NULL);
}
