/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:54:54 by aainhaja          #+#    #+#             */
/*   Updated: 2022/07/23 16:12:49 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>
#include <sys/time.h>

void routine(void *arg)
{
	t_philo *philo;
	philo = arg;
	pthread_mutex_lock(&mutex[philo->i]);
	printf("\nPhilosopher % d picks up the left fork ", philo->i + 1);
	pthread_mutex_lock(&mutex[(philo->i + 1) % philo->nb]);
	printf("\nPhilosopher % d picks up the right fork ", philo->i + 1);
	printf("\nPhilosopher % d is eating ", philo->i + 1);
	sleep(1);
	pthread_mutex_unlock(&mutex[philo->i]);
	printf("\nPhilosopher %d places down the left fork ",philo->i + 1);
	pthread_mutex_unlock(&mutex[(philo->i + 1) % philo->nb]);
	printf("\nPhilosopher % d places down the right fork ",philo->i + 1);
	printf("\nPhilosopher % d is thinking ", philo->i + 1);
}

void philosophers(t_philo arg)
{
	mutex = malloc(sizeof(pthread_mutex_t) * arg.nb + 1);
    int i;
	t_philo *philo;
	t_philo *head;

	t = malloc(sizeof(pthread_t) * arg.nb + 1);
	i = arg.nb - 1;

	philo = NULL;
	while(0 <= i)
	{
		head = malloc(sizeof(t_philo) * 8);
		head->nb = arg.nb;
    	head->nb_of_forks = arg.nb;
    	head->time_to_die = arg.time_to_die;
    	head->time_to_eat = arg.time_to_eat;
    	head->time_to_sleep = arg.time_to_sleep;
    	head->nb_of_eat = arg.nb_of_eat;
		head->next = philo;

		philo = head;
		i--;
	}
	i = 0;
	while(i < arg.nb)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	i = 0;
	
	while(1)
	{
		i = 0;
		head = philo;
		while(i < arg.nb)
		{
			head->i = i;
			pthread_create(&t[i],NULL, (void *) routine, head);
			head = head->next;
			i+=2;
		}
		usleep(100);
		i = 1;
		while(i < arg.nb)
		{
			head->i = i;
			pthread_create(&t[i],NULL, (void *) routine, head);
			head = head->next;
			i+=2;
		}
	i = 0;
	while(i < arg.nb)
	{
		pthread_join(t[i],NULL);
		i++;
	}
	}
	i = 0;
	while(i < arg.nb)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
}
int main(int argc,char **argv)
{
    t_philo arg;
	if(argc == 6)
	{
    	arg.nb = atoi(argv[1]);
    	arg.nb_of_forks = arg.nb;
    	arg.time_to_die = atoi(argv[2]);
    	arg.time_to_eat = atoi(argv[3]);
    	arg.time_to_sleep = atoi(argv[4]);
    	arg.nb_of_eat = atoi(argv[5]);
		philosophers(arg);
	}
}