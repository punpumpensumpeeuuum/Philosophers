/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:28:38 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/08 23:40:46 by elemesmo         ###   ########.fr       */
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
	int				dead;
	int				fffork;
	long			lastmeal;
	struct l_main	*main;
	pthread_t		t;
	pthread_t		thread;
	pthread_mutex_t	a;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
}	t_philo;

typedef struct l_main
{
	int				numphilo;
	int				tdie;
	int				teat;
	int				tsleepy;
	int				nummeal;
	int				stop;
	int				dontprint;
	long int		start;
	t_philo			*philo;
	pthread_mutex_t	printer;
	pthread_mutex_t	d;
}	t_main;

int			ft_isdigitbroken(char **str, int ac);
int			ft_atoi(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

void		setidforeach(t_main *main, int max, char **av, int ac);
int			startphilo(t_main *main);
void		*philololo(void	*ele);
void		checkfork(t_main *main);

long int	timestamps(void);
void		betterusleep(int time);
void		print(t_philo *philo, char *text);
void		freefree(t_main *main);

#endif