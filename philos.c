/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:51:27 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/10 17:56:26 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forkfork(t_philo *philo)
{
	if (checkstop(philo) == 1)
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->l_fork));
		print(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->r_fork);
		print(philo, "has taken a fork\n");
	}
	else if (checkstop(philo) != 1 && philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print(philo, "has taken a fork\n");
		pthread_mutex_lock(&(philo->l_fork));
		print(philo, "has taken a fork\n");
	}
	if (checkstop(philo) == 1)
	{
		pthread_mutex_unlock(&(philo->l_fork));
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
}

void	eat(t_philo *philo)
{
	if (checkstop(philo) == 1)
		return ;
	print(philo, "is eating\n");
	pthread_mutex_lock(&philo->inc);
	philo->numeat++;
	pthread_mutex_unlock(&philo->inc);
	pthread_mutex_lock(&philo->meal);
	philo->lastmeal = timestamps();
	pthread_mutex_unlock(&philo->meal);
	betterusleep(philo->main->teat);
	if (checkstop(philo) == 1)
	{
		pthread_mutex_unlock(&(philo->l_fork));
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_unlock(&(philo->l_fork));
	pthread_mutex_unlock(philo->r_fork);
	print(philo, "is sleeping\n");
	if (checkstop(philo) == 1)
		return ;
	betterusleep(philo->main->tsleepy);
	print(philo, "is thinking\n");
	if (checkstop(philo) == 1)
		return ;
}

void	*checkdeath(void *philooo)
{
	t_philo	*philo;

	philo = (t_philo *)philooo;
	while (1)
	{
		if (checkstop(philo) == 1)
			break ;
		betterusleep(1);
		if (deadtwo(philo) == 1)
			break ;
		pthread_mutex_lock(&philo->check);
		pthread_mutex_lock(&(philo->main->ded));
		if (philo->main->stop == 1 || philo->doneeating == 1)
		{
			pthread_mutex_unlock(&(philo->main->ded));
			pthread_mutex_unlock(&philo->check);
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->main->ded));
		pthread_mutex_unlock(&philo->check);
	}
	betterusleep(10);
	return (NULL);
}

int	donedone(t_philo *philo)
{
	if (philo->numeat == philo->main->nummeal)
	{
		pthread_mutex_lock(&philo->check);
		philo->doneeating = 1;
		pthread_mutex_unlock(&philo->check);
		return (1);
	}
	return (0);
}

void	*philololo(void *arg)
{
	t_philo		*philo;
	t_main		*main;

	philo = (t_philo *)arg;
	main = philo->main;
	pthread_create(&philo->t, NULL, checkdeath, philo);
	if (philo->id == 1 && philo->id % 2 == 1)
		betterusleep(50);
	while (philo->doneeating == 0)
	{
		if (checkstop(philo) == 1)
			break ;
		forkfork(philo);
		if (checkstop(philo) == 1)
			break ;
		eat(philo);
		if (donedone(philo) == 1 || checkstop(philo) == 1)
			break ;
	}
	pthread_join(philo->t, NULL);
	return (NULL);
}
