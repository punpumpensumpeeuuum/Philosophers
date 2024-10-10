/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:51:27 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/10 01:24:29 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forkfork(t_philo *philo)
{
	if (checkstop(philo) == 1)
		return ;
	if (philo->id < (philo->id + 1) % philo->main->numphilo)
	{
		pthread_mutex_lock(&(philo->l_fork));
		print(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->r_fork);
		print(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print(philo, "has taken a fork\n");
		pthread_mutex_lock(&(philo->l_fork));
		print(philo, "has taken a fork\n");
	}
	if (checkstop(philo) == 1)
		return ;
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
	betterusleep(philo->main->tsleepy);
	print(philo, "is thinking\n");
}

void	*checkdeath(void *philooo)
{
	t_philo	*philo;

	philo = (t_philo *)philooo;
	while (1)
	{
		pthread_mutex_lock(&philo->main->ded);
		if (philo->main->stop == 1)
			break ;
		pthread_mutex_unlock(&philo->main->ded);
		betterusleep(1);
		if (deadtwo(philo) == 1)
			break ;
		pthread_mutex_lock(&(philo->main->ded));
		pthread_mutex_lock(&philo->check);
		if (philo->main->stop == 1 || philo->doneeating == 1)
		{
			pthread_mutex_unlock(&(philo->main->ded));
			pthread_mutex_unlock(&philo->check);
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->main->ded));
		pthread_mutex_unlock(&philo->check);
	}
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
	while (main->stop == 0 || philo->doneeating == 0)
	{
		if (checkstop(philo) == 1)
			break ;
		forkfork(philo);
		if (checkstop(philo) == 1)
			break ;
		eat(philo);
		if (donedone(philo) == 1)
			break ;
	}
	pthread_join(philo->t, NULL);
	return (NULL);
}

// potetial deadlock com 3 ou 5
// norminete
// so pa 1 philo