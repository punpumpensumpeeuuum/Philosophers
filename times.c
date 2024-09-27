/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:04:39 by dinda-si          #+#    #+#             */
/*   Updated: 2024/09/27 16:03:09 by dinda-si         ###   ########.fr       */
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
	int	now;

	now = timestamps();
	while (timestamps() - now < time)
		usleep(time / 10);
}

long long	timestamps(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
