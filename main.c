/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvillefr <jvillefr@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:57:16 by jvillefr          #+#    #+#             */
/*   Updated: 2023/07/06 14:47:10 by jvillefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	printf_status(char *str, t_philo *philo)
{
	long int		time;

	time = -1;
	time = timestamp() - philo->table_data->start_t;
	if (time >= 0 && time <= 2147483647 && !check_death(philo, 0))
	{
		printf("%ld ", time);
		printf("Philo %d %s", philo->id, str);
	}
}

int	ft_atoi(const char *str)
{
	int		negative;
	long	nb;

	negative = 1;
	nb = 0;
	while ((*str >= '\t' && *str <= '\r') || (*str == ' '))
		str++;
	if (*str == '-')
	{
		negative = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + *str - 48;
		str++;
		if (nb * negative > 2147483647)
			return (-1);
		if (nb * negative < -2147483648)
			return (0);
	}
	return (nb * negative);
}

int	ft_death(t_table *table)
{
	pthread_mutex_lock(&table->data.dead_mutex);
	if (table->data.stop)
	{
		pthread_mutex_unlock(&table->data.dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->data.dead_mutex);
	return (0);
}

void	stop(t_table *table)
{
	int	i;

	i = -1;
	while (!ft_death(table))
		ft_usleep(1);
	while (++i < table->data.nbr_philo)
		pthread_join(table->philo[i].thread_id, NULL);
	pthread_mutex_destroy(&table->data.write_mutex);
	i = -1;
	while (++i < table->data.nbr_philo)
		pthread_mutex_destroy(&table->philo[i].left_fork);
	if (table->data.stop == 2)
		printf("Each philosopher ate %d time(s) at least\n", \
		table->data.max_eat);
	free(table->philo);
}

int	main(int argc, char **argv)
{
	t_table		table;

	if (!check_args(argc, argv) || !(parse_args(argv, &table)))
		return (ft_exit("Invalid Arguments\n"));
	table.philo = malloc(sizeof(t_philo) * table.data.nbr_philo);
	if (!table.philo)
		return (ft_exit("Malloc failed\n"));
	init_table(&table);
	if (!start_thread(&table))
	{
		free(table.philo);
		return (0);
	}
	stop(&table);
}
