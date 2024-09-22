/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:51:27 by elemesmo          #+#    #+#             */
/*   Updated: 2024/09/22 22:46:29 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	startphilo(t_main *main)
{
	int	i;

	i = 0;
	while (main->numphilo <= i)
	{
		pthread_mutex_init(&(main->philo[i].l_fork), NULL);
		if (i == main->numphilo - 1)
			main->philo[i].r_fork = &main->philo[0].l_fork;
		else
			main->philo[i].r_fork = &main->philo[i + 1].l_fork;
		if (pthread_create(&main->philo[i].thread,
				NULL, &philololo, &main->philo[i]) != 0)
			return ;
	}
	// ver se os philos sao pares
	// antes de tudo ver se eles tao mortos
	// funcao pa eles terem os dois garfos
	// comer e pousar o garfo
}

void	*philololo(void	*ele)
{
	t_philo	*phi;

	phi = (t_philo *)ele;
	if (phi->id % 2 == 0)
		//comer
	while (checkdeath() == 0)
	{
		//tirar o garfo dos outros
		// comer 
	}
}
