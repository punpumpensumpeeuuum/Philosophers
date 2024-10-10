/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:27:27 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/10 01:23:52 by elemesmo         ###   ########.fr       */
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
	setidforeach(main, i, av, ac);
	main->tdie = ft_atoi(av[2]);
	main->teat = ft_atoi(av[3]);
	main->tsleepy = ft_atoi(av[4]);
	main->dontprint = 0;
	pthread_mutex_init(&(main->ded), NULL);
	pthread_mutex_init(&(main->para), NULL);
	pthread_mutex_init(&(main->printer), NULL);
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
	{
		printf("%d\n", startphilo(&main));
		freefree(&main);
	}
}

		// if (philo->id == 1) {
		// 	printf("$$1	%ld\n", timestamps());
		// 	printf("$$2	%ld\n", philo->lastmeal);
		// 	printf("$$3	%ld\n", timestamps() - philo->lastmeal);
		// 	printf("$$4	%ld\n", (long)philo->main->tdie);}
