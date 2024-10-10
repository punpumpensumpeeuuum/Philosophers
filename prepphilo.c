/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepphilo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:33:51 by elemesmo          #+#    #+#             */
/*   Updated: 2024/10/10 17:57:43 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	deadtwo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->check));
	pthread_mutex_lock(&philo->meal);
	pthread_mutex_lock(&philo->main->para);
	if (philo->doneeating == 0 && philo->lastmeal > 0
		&& timestamps() - philo->lastmeal >= (long)philo->main->tdie)
	{
		pthread_mutex_unlock(&philo->main->para);
		pthread_mutex_unlock(&philo->meal);
		pthread_mutex_lock(&(philo->main->ded));
		philo->main->stop = 1;
		pthread_mutex_unlock(&(philo->main->ded));
		print(philo, "died\n");
		pthread_mutex_unlock(&(philo->check));
		return (1);
	}
	pthread_mutex_unlock(&philo->main->para);
	pthread_mutex_unlock(&philo->meal);
	pthread_mutex_unlock(&(philo->check));
	return (0);
}

int	checkstop(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->ded);
	if (philo->main->stop == 1)
	{
		pthread_mutex_unlock(&philo->main->ded);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->ded);
	return (0);
}

void	prepthread(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->numphilo)
	{
		pthread_mutex_init(&(main->philo[i].l_fork), NULL);
		if (i == main->numphilo - 1)
			main->philo[i].r_fork = &main->philo[0].l_fork;
		else
			main->philo[i].r_fork = &main->philo[i + 1].l_fork;
		i++;
	}
	i = 0;
	while (i < main->numphilo)
	{
		if (pthread_create(&main->philo[i].thread,
				NULL, &philololo, &main->philo[i]) != 0)
			return ;
		i++;
	}
}

int	startphilo(t_main *main)
{
	int	i;

	i = 0;
	if (main->numphilo == 1)
	{
		printf("1ms 0 died");
		return (4);
	}
	prepthread(main);
	while (i < main->numphilo)
	{
		if (pthread_join(main->philo[i].thread, NULL) != 0)
			return (2);
		i++;
	}
	main->stop = 1;
	return (0);
}
