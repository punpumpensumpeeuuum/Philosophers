/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:28:38 by elemesmo          #+#    #+#             */
/*   Updated: 2024/09/25 01:21:38 by elemesmo         ###   ########.fr       */
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
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
}	t_philo;

typedef struct l_main
{
	int				numphilo;			
	int				tdie;
	int				teat;
	int				tsleepy;
	int				stop;
	long int		start;
	t_philo			*philo;
	pthread_mutex_t	printer;
}	t_main;

int			ft_isdigitbroken(char **str, int ac);
int			ft_atoi(const char *str);

void		setidforeach(t_main *main, int max, char **av, int ac);
void		startphilo(t_main *main);
void		*philololo(void	*ele);
int			nodead(t_philo *philo, int i);

long long	timestamps(void);
void		betterusleep(int time);
void		print(t_philo *philo, char *text);


#endif