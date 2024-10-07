/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:27:27 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/07 18:24:02 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (i < nmemb * size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}

int	setval(t_main *main, char **av, int ac)
{
	int	i;

	i = ft_atoi(av[1]);
	if (ft_isdigitbroken(av, ac) == 1)
		return (1);
	main->start = timestamps();
	main->stop = 0;
	main->philo = ft_calloc(i + 1, sizeof(t_philo));
	if (!main->philo)
		return (2);
	main->numphilo = i;
	main->cicle = 0;
	setidforeach(main, i, av, ac);
	main->tdie = ft_atoi(av[2]);
	main->teat = ft_atoi(av[3]);
	main->tsleepy = ft_atoi(av[4]);
	pthread_mutex_init(&(main->printer), NULL);
	pthread_mutex_init(&(main->a), NULL);
	pthread_mutex_init(&(main->pares), NULL);
	if (main->numphilo <= 0 || main->tdie <= 0 || \
		main->teat <= 0 || main->tsleepy <= 0)
		return (3);
	return (0);
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 5 && ac != 6)
		return (0);
	if (setval(&main, av, ac) != 1)
		startphilo(&main);
	freefree(&main);
}

// allocs pro freear
// ver melhor a logica do ciclo par e tal
