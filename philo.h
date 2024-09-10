/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:28:38 by elemesmo          #+#    #+#             */
/*   Updated: 2024/09/10 22:54:35 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct l_philo
{
	int				id;
	int				numeat;
	struct l_main	*main;
}	t_philo;

typedef struct l_main
{
	int				numphilo;			
	int				tdie;
	int				teat;
	int				tsleepy;
	t_philo			*philo;
}	t_main;

int		ft_isdigitbroken(char **str, int ac);
int		ft_atoi(const char *str);

void	setidforeach(t_main *main, int max, char **av, int ac);

#endif