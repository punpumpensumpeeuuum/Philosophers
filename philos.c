/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:51:27 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/09 17:24:50 by dinda-si         ###   ########.fr       */
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
		i++;
	}
	i = 0;
	while (i < main->numphilo)
	{
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
		printf("%d DONEEATING:%d    id:%d eat:%d\n",i,main->philo[i].doneeating ,main->philo[i].id ,main->philo[i].numeat);
		i++;
	}
	main->stop = 1;
	return (0);
}

void forkfork(t_philo *philo)
{
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
}

void	eat(t_philo *philo)
{
	print(philo, "is eating\n");
	pthread_mutex_lock(&philo->inc);
	philo->numeat++;
	pthread_mutex_unlock(&philo->inc);
	pthread_mutex_lock(&philo->meal);
	philo->lastmeal = timestamps();
	pthread_mutex_unlock(&philo->meal);
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
	while (1)
	{
		pthread_mutex_lock(&philo->main->ded);
		if (philo && philo->main->stop == 1)
			break;
		pthread_mutex_unlock(&philo->main->ded);
		betterusleep(1);
		pthread_mutex_lock(&(philo->check));
		pthread_mutex_lock(&philo->meal);
		pthread_mutex_lock(&philo->main->para);
		// if (philo->id == 1) {
		// 	printf("$$1	%ld\n", timestamps());
		// 	printf("$$2	%ld\n", philo->lastmeal);
		// 	printf("$$3	%ld\n", timestamps() - philo->lastmeal);
		// 	printf("$$4	%ld\n", (long)philo->main->tdie);}
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
			return (NULL);
		}
		pthread_mutex_unlock(&philo->main->para);
		pthread_mutex_unlock(&philo->meal);
		pthread_mutex_unlock(&(philo->check));
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

void	*philololo(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_main *main = philo->main;

	pthread_create(&philo->t, NULL, checkdeath, philo);
	if (philo->id == 1 && philo->id % 2 == 1)
		betterusleep(50);
	while (main->stop == 0 || philo->doneeating == 0)
	{
		pthread_mutex_lock(&philo->main->ded);
		if (philo->main->stop == 1)
			break;
		pthread_mutex_unlock(&philo->main->ded);
		forkfork(philo);
		pthread_mutex_lock(&philo->main->ded);
		if (philo->main->stop == 1)
		 	break;
		pthread_mutex_unlock(&philo->main->ded);
		eat(philo);
		if (philo->numeat == philo->main->nummeal)
		{
			pthread_mutex_lock(&philo->check);
			philo->doneeating = 1;
			pthread_mutex_unlock(&philo->check);
			// pthread_mutex_lock(&philo->main->ded);
			// main->stop = 1;
			// pthread_mutex_unlock(&philo->main->ded);
			break;
		}
	}
	pthread_join(philo->t, NULL);
	return (NULL);
}

// potetial deadlock com 3 ou 5
// norminete
// so pa 1 philo