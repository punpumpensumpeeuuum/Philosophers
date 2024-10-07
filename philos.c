/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:51:27 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/08 00:41:31 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	startphilo(t_main *main)
{
	int	i;

	i = 0;
	// checkfork(main);
	while (i < main->numphilo)
	{
		pthread_mutex_init(&(main->philo[i].l_fork), NULL);
		if (i == main->numphilo - 1)
			main->philo[i].r_fork = &main->philo[0].l_fork;
		else
			main->philo[i].r_fork = &main->philo[i + 1].l_fork;
		if (pthread_create(&main->philo[i].thread,
				NULL, &philololo, &main->philo[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < main->numphilo)
	{	
		if (pthread_join(main->philo[i].thread, NULL) != 0)
			return (2);
		if (pthread_join(main->philo[i].t, NULL) != 0)
			return (3);
		i++;
	}
	return (0);
}

void	forkfork(t_philo *philo)
{
	if (philo->main->stop == 1)
		return ;
	pthread_mutex_lock(&(philo->l_fork));
	print(philo, "has taken a fork\n");
	if (philo->main->stop == 1)
		return ;
	pthread_mutex_lock(philo->r_fork);
	print(philo, "has taken a fork\n");
}

void	eat(t_philo *philo)
{
	if (philo->main->stop == 1)
		return ;
	print(philo, "is eating\n");
	philo->numeat--;
	philo->lastmeal = timestamps();
	betterusleep(philo->main->teat);
	pthread_mutex_unlock(&(philo->l_fork));
	pthread_mutex_unlock(philo->r_fork);
	if (philo->main->stop == 1)
		return ;
	print(philo, "is sleeping\n");
	betterusleep(philo->main->tsleepy);
	if (philo->main->stop == 1)
		return ;
	print(philo, "is thinking\n");
}

void	*checkdeath(void *philooo)
{
	t_philo	*philo;

	philo = (t_philo *)philooo;
	while (philo->main->stop == 0)
	{	
		pthread_mutex_lock(&(philo->main->a));
		if (timestamps() - philo->lastmeal >= (long)philo->main->tdie)
		{
			philo->main->stop = 1;
			print(philo, "has diedAHBUYAVSUGFVBAISVUGBIASBVGI\n");
			pthread_mutex_unlock(&(philo->main->a));
			return (NULL);
		}
	}
	pthread_mutex_unlock(&(philo->main->a));
	betterusleep(100);
	return (NULL);
}

void	philorotine(t_philo *philo)
{
	t_main *main = philo->main;

	if (philo->main->stop == 1)
		return ;
	if (philo->dead == 0)
	{
		pthread_create(&philo->t, NULL, checkdeath, philo);
		philo->dead++;
	}
	if (philo->main->stop == 1)
		return ;
	forkfork(philo);
	if (philo->main->stop == 1)
		return ;
	eat(philo);
	if (philo->numeat == 0)
		main->stop = 1;
}

void	*philololo(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_main *main = philo->main;

	betterusleep(1);
	while (main->stop == 0)
	{
		if (philo->id % 2 == 0)
		{
			while (main->cicle != 0)
			{
				pthread_mutex_unlock(&main->pares);
				betterusleep(100);
				pthread_mutex_lock(&main->pares);
			}
		}
		else
		{
			while (main->cicle != 1)
			{
				pthread_mutex_unlock(&main->pares);
				betterusleep(100);
				pthread_mutex_lock(&main->pares);
			}
		}
		pthread_mutex_lock(&main->pares);
		philorotine(philo);
		if (main->cicle == 0)
			main->cicle = 1;
		else
			main->cicle = 0;
		pthread_mutex_unlock(&main->pares);
		betterusleep(100);
	}
	return (NULL);
}
