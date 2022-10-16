/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:42:08 by aainhaja          #+#    #+#             */
/*   Updated: 2022/10/16 18:15:43 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
# include <pthread.h>
#include <sys/time.h> 
#include <sys/signal.h>
#include <unistd.h>
#include <signal.h>

#include <semaphore.h>

typedef struct s_inside
{
	sem_t *sem;
	sem_t *write;
	sem_t *time;
	sem_t *d;
	sem_t *eat;
	pthread_t death;
	int dead;
}	t_inside;

typedef struct s_philo {
	int nb;
	int i;
	int l;
	long time_beg;
	int time_to_die;
	int time_to_sleep;
	int time_to_eat;
	int nb_of_eat;
	int pid;
	long time_start;
	int *k;
	t_inside *set;
	struct s_philo *next;
}				t_philo;

void	ft_putstr(char *s);
void	ft_putchar(char c);
void	ft_putnbr(int n);
long		get_time_now();
void	ft_print(char *s1,t_philo *head,char *s2);
#endif