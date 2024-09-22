/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:27:27 by elemesmo          #+#    #+#             */
/*   Updated: 2024/09/22 22:19:47 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *text);

int	setval(t_main *arg, char **av, int ac)
{
	int	i;

	i = ft_atoi(av[1]);
	if (ft_isdigitbroken(av, ac) == 1)
		return (1);
	arg->philo = malloc(sizeof(t_philo) * i + 1);
	arg->numphilo = i;
	setidforeach(arg, i, av, ac);
	arg->tdie = ft_atoi(av[2]);
	arg->teat = ft_atoi(av[3]);
	arg->tsleepy = ft_atoi(av[4]);
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
