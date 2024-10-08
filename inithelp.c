/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inithelp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:35:32 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/09 16:06:38 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char )s1[i] - (unsigned char )s2[i]);
		i++;
	}
	if (i != n)
		return ((unsigned char )s1[i] - (unsigned char )s2[i]);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	a;
	int	num;

	i = 0;
	a = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-')
	{
		i++;
		a *= -1;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	return (num * a);
}

int	ft_isdigitbroken(char **str, int ac)
{
	int	i;
	int	j;

	j = 1;
	while (j < ac)
	{
		i = 0;
		while (str[j][i])
		{
			if (str[j][i] >= '0' && str[j][i] <= '9')
				i++;
			else
				return (1);
		}
		j++;
	}
	return (0);
}

void	numeatmaybe(t_main *main, int numero, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		main->philo[i].numeat = numero;
		i++;
	}
}

void	setidforeach(t_main *main, int max, char **av, int ac)
{
	int	i;
	int	id;

	id = 1;
	i = 0;
	while (i < max)
	{
		main->philo[i].doneeating = 0;
		main->philo[i].id = id;
		main->philo[i].numeat = 0;
		main->philo[i].dead = 0;
		main->philo[i].main = main;
		main->philo[i].fffork = 0;
		pthread_mutex_init(&(main->philo[i].check), NULL);
		pthread_mutex_init(&(main->philo[i].meal), NULL);
		pthread_mutex_init(&(main->philo[i].inc), NULL);
		id++;
		i++;
	}
	if (ac == 6)
		main->nummeal = ft_atoi(av[5]);
	else
		main->nummeal = -1;
}
