/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:04:39 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/07 23:16:43 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *text)
{
	long int	time;

	pthread_mutex_lock(&(philo->main->printer));
	time = timestamps() - philo->main->start;
	printf("%ldms %d %s",time, philo->id , text);
	pthread_mutex_unlock(&(philo->main->printer));
}

void	betterusleep(int time)
{
	long int	now;

	now = timestamps();
	while (timestamps() - now < time)
		usleep(time / 10);
}

long int	timestamps(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	freefree(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->numphilo)
	{
		pthread_mutex_destroy(&main->philo[i].l_fork);
		pthread_mutex_destroy(main->philo[i].r_fork);
		i++;
	}
	free(main->philo);
	pthread_mutex_destroy(&main->printer);
	pthread_mutex_destroy(&main->a);
	pthread_mutex_destroy(&main->pares);
}
