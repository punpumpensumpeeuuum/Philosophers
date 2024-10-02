/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:51:27 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/02 17:20:03 by dinda-si         ###   ########.fr       */
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
		i++;
	}
	return (0);
}

void	forkfork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->l_fork));
	print(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->r_fork);
	print(philo, "has taken a fork\n");
}

void	eat(t_philo *philo)
{
	print(philo, "is eating\n");
	philo->numeat--;
	philo->lastmeal = timestamps();
	betterusleep(philo->main->teat);
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
	pthread_mutex_lock(&(philo->main->a));
	// printf("time: %lld\n", timestamps());
	// printf("meal: %ld\n", philo->lastmeal);
	// printf("tdie: %ld\n", (long)philo->main->tdie);
	if (philo->main->stop == 0 && timestamps() - philo->lastmeal >= (long)philo->main->tdie)
	{
		philo->main->stop = 1;
		print(philo, "has diedAHBUYAVSUGFVBAISVUGBIASBVGI\n");
		pthread_mutex_unlock(&(philo->main->a));
		return (NULL);
	}
	pthread_mutex_unlock(&(philo->main->a));
	return (NULL);
}

void	philorotine(t_philo *philo)
{
	pthread_t	t;
	
	pthread_create(&t, NULL, checkdeath, philo);
	forkfork(philo);
	eat(philo);
	if (philo->numeat == 0)
	{
		philo->main->stop = 1;
		return ;
	}
	return ;
}

void	*philololo(void	*phi)
{
	t_philo		*philo;

	philo = (t_philo *)phi;
	while (philo->main->stop == 0)
	{
		if (philo->main->cicle % 2 == 0) // se for par
		{
			if (!(philo->id % 2 == 0)) // se o philo for impar
				pthread_mutex_lock(&(philo->main->pares));
			else
				philorotine(philo);
			pthread_mutex_unlock(&(philo->main->pares));
		}
		else
		{
			if ((philo->id % 2 == 0))
				pthread_mutex_lock(&(philo->main->pares));
			else
				philorotine(philo);
			pthread_mutex_unlock(&(philo->main->pares));
		}
		philo->main->cicle++;
	}
	return (NULL);
}
