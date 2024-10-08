/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:51:27 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/09 00:27:15 by elemesmo         ###   ########.fr       */
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
	if (philo->main->stop == 1) {
		printf("ola%d\n", philo->id);
		return ; }
	print(philo, "is eating\n");
	philo->numeat--;
	philo->lastmeal = timestamps();
	betterusleep(philo->main->teat);
	pthread_mutex_unlock(&(philo->l_fork));
	pthread_mutex_unlock(philo->r_fork);
	if (philo->main->stop == 1) {
		printf("ola%d\n", philo->id);
		return ; }
	print(philo, "is sleeping\n");
	betterusleep(philo->main->tsleepy);
	if (philo->main->stop == 1) {
		printf("ola%d\n", philo->id);
		return ; }
	print(philo, "is thinking\n");
}

void	*checkdeath(void *philooo)
{
	t_philo	*philo;

	philo = (t_philo *)philooo;
	while (1)
	{
		betterusleep(1);
		pthread_mutex_lock(&(philo->a));
		// if (philo->id == 3) {
		// 	printf("$$1	%ld\n", timestamps());
		// 	printf("$$2	%ld\n", philo->lastmeal);
		// 	printf("$$3	%ld\n", timestamps() - philo->lastmeal);
		// 	printf("$$4	%ld\n", (long)philo->main->tdie);}
		if (philo->lastmeal > 0 && timestamps() - philo->lastmeal >= (long)philo->main->tdie)
		{
			pthread_mutex_lock(&(philo->main->d));
			philo->main->stop = 1;
			pthread_mutex_unlock(&(philo->main->d));
			print(philo, "died\n");
			pthread_mutex_unlock(&(philo->a));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->a));
		pthread_mutex_lock(&(philo->main->d));
		if (philo->main->stop == 1)
		{
			pthread_mutex_unlock(&(philo->main->d));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->main->d));
	}
	pthread_mutex_unlock(&(philo->a));
	betterusleep(1);
	return (NULL);
}

void	*philololo(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_main *main = philo->main;

	betterusleep(1);
	pthread_create(&philo->t, NULL, checkdeath, philo);
	if (philo->id % 2 == 1)
		betterusleep(philo->main->teat);
	while (main->stop == 0)
	{
		if (philo->main->stop == 1) {
			printf("ola%d\n", philo->id);
			return (NULL); }
		forkfork(philo);
		if (philo->main->stop == 1) {
			printf("ola%d\n", philo->id);
			return (NULL); }
		eat(philo);
		if (philo->numeat == 0)
			main->stop = 1;
		}
	return (NULL);
}

//fazer flag pa verificar os garfos
//testar com if (philo->id % 2 == 1)