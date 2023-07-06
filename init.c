/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvillefr <jvillefr@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:58:04 by jvillefr          #+#    #+#             */
/*   Updated: 2023/06/27 16:09:32 by jvillefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long int	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	init_mutex(t_table *table)
{
	pthread_mutex_init(&table->data.write_mutex, NULL);
	pthread_mutex_init(&table->data.dead_mutex, NULL);
	pthread_mutex_init(&table->data.eat_mutex, NULL);
	pthread_mutex_init(&table->data.finish_mutex, NULL);
}

int	parse_args(char **argv, t_table *table)
{
	table->data.nbr_philo = ft_atoi(argv[1]);
	table->data.time_to_die = ft_atoi(argv[2]);
	table->data.time_to_eat = ft_atoi(argv[3]);
	table->data.sleep = ft_atoi(argv[4]);
	table->data.max_eat = -1;
	if (argv[5])
		table->data.max_eat = ft_atoi(argv[5]);
	if (table->data.nbr_philo <= 0 || table->data.time_to_die <= 0 || \
		table->data.time_to_eat <= 0 || table->data.sleep <= 0)
		return (0);
	return (1);
}

int	init_table(t_table *table)
{
	int	i;

	i = 0;
	table->data.start_t = timestamp();
	table->data.stop = 0;
	table->data.philo_done = 0;
	init_mutex(table);
	while (i < table->data.nbr_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].last_time_eat = table->data.start_t;
		table->philo[i].eat_time = 0;
		table->philo[i].done = 0;
		table->philo[i].right_fork = NULL;
		pthread_mutex_init(&table->philo[i].left_fork, NULL);
		if (table->data.nbr_philo == 1)
			return (1);
		if (i == table->data.nbr_philo - 1)
			table->philo[i].right_fork = &table->philo[0].left_fork;
		else
			table->philo[i].right_fork = &table->philo[i + 1].left_fork;
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		return (0);
	}
	while (i < argc)
	{
		if (str_only_digit(argv[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
