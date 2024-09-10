/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:27:27 by elemesmo          #+#    #+#             */
/*   Updated: 2024/09/10 22:53:26 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setval(t_main *arg, char **av, int ac)
{
	int	i;

	i = ft_atoi(av[1]);
	if (ft_isdigitbroken(av, ac) == 1)
		return ;
	arg->philo = malloc(sizeof(t_philo) * i + 1);
	arg->numphilo = i;
	setidforeach(arg, i, av, ac); // dar o id a cada um ne
	i = ft_atoi(av[2]);
	arg->tdie = i;
	i = ft_atoi(av[3]);
	arg->teat = i;
	i = ft_atoi(av[4]);
	arg->tsleepy = i;
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 5 && ac != 6)
		return (0);
	setval(&main, av, ac);
}
