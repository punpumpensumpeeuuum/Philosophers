/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:27:27 by elemesmo          #+#    #+#             */
/*   Updated: 2024/09/25 01:19:36 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setval(t_main *arg, char **av, int ac)
{
	int	i;

	i = ft_atoi(av[1]);
	if (ft_isdigitbroken(av, ac) == 1)
		return (1);
	arg->start = timestamps();
	arg->stop = 0;
	arg->philo = malloc(sizeof(t_philo) * i + 1);
	arg->numphilo = i;
	setidforeach(arg, i, av, ac);
	arg->tdie = ft_atoi(av[2]);
	arg->teat = ft_atoi(av[3]);
	arg->tsleepy = ft_atoi(av[4]);
	pthread_mutex_init(&(arg->printer), NULL);
	if (arg->numphilo <= 0 || arg->tdie <= 0 || \
		arg->teat <= 0 || arg->tsleepy <= 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 5 && ac != 6)
		return (0);
	if (setval(&main, av, ac) != 1)
		startphilo(&main);
}
