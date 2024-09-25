/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:04:39 by elemesmo          #+#    #+#             */
/*   Updated: 2024/09/25 00:05:43 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *text)
{
	long int	time;

	pthread_mutex_lock(&(philo->main->printer));
	time = timestamps() - philo->main->start;
	printf("%ld %d %s\n",time, philo->id , text);
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
