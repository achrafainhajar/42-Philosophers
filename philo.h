/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:59:46 by aainhaja          #+#    #+#             */
/*   Updated: 2022/07/23 15:41:10 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
# include <pthread.h>
 #include <sys/time.h>
#include <unistd.h>


typedef struct s_inside
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	dead;
}	t_inside;

typedef struct s_philo {
	int nb;
	int i;
	float time_beg;
	int nb_of_forks;
	float time_to_die;
	int time_to_sleep;
	int time_to_eat;
	int nb_of_eat;
	float time_start;
	t_inside *set;
	struct s_philo *next;
}				t_philo;



#endif
