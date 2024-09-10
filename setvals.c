/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setvals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:51:27 by elemesmo          #+#    #+#             */
/*   Updated: 2024/09/10 22:54:51 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setidforeach(t_main *main, int max, char **av, int ac)
{
	int	i;
	int	id;

	id = 1;
	i = 0;
	while (i < max)
	{
		main->philo[i].id = id;
		id++;
		i++;
	}
	if (ac == 6)
	{
		id = ft_atoi(av[5]);
		i = 0;
		while (i < max)
		{
			main->philo[i].numeat = id;
			i++;
		}
	}
}
