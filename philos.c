/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:51:27 by dinda-si          #+#    #+#             */
/*   Updated: 2024/09/27 16:17:31 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	startphilo(t_main *main)
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
	if (philo->main->stop == 0 && timestamps() - philo->lastmeal >= (long)philo->main->tdie)
	{
		philo->main->stop = 1;
		print(philo, "has died\n");
		pthread_mutex_unlock(&(philo->main->a));
		return (NULL);
	}
	pthread_mutex_unlock(&(philo->main->a));
	return (NULL);
}

void	*philololo(void	*phi)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)phi;
	// printf("%d\n", philo->id);
	if (philo->id % 2 == 0)
		betterusleep(philo->main->teat / 10);
	while (philo->main->stop == 0)
	{
		pthread_create(&t, NULL, checkdeath, philo);
		forkfork(philo);
		// printf("c\n");
		eat(philo);
		// printf("d\n");
		if (philo->numeat < 0)
		{

			// printf("e\n");
			return (NULL);
		}
		pthread_join(t, NULL);
	}
	return (NULL);
}
