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

float get_time_now(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	return(tv.tv_usec * 0.001);
}
void check_death(t_philo *arg)
{	
	float i;
	i = get_time_now();
		pthread_mutex_lock(&arg->set->dead);
	if(i - arg->time_start > arg->time_to_die)
	{
		printf("\nPHIlO %d Died \n",arg->i + 1);
		exit(1);
	}
	else
		pthread_mutex_unlock(&arg->set->dead);
}

void eating(t_philo *philo)
{
	printf("\nPhilosopher % d is eating ", philo->i + 1);
	usleep(philo->time_to_eat * 1000);
}

void sleeping(t_philo *philo)
{
	printf("\nPhilosopher % d is sleeping ", philo->i + 1);
	usleep(philo->time_to_sleep * 1000);
}

void routine(void *arg)
{
	t_philo *philo;
	philo = arg;
	if(philo->i % 2)
		usleep(1500);
	pthread_mutex_lock(&philo->set->mutex[philo->i]);
	printf("\n Philosopher % d picks up the left fork ", philo->i + 1);
	pthread_mutex_lock(&philo->set->mutex[(philo->i + 1) % philo->nb]);
	printf("\nPhilosopher % d picks up the right fork ", philo->i + 1);
	eating(philo);
	philo->time_start = get_time_now();
	pthread_mutex_unlock(&philo->set->mutex[philo->i]);
	printf("\nPhilosopher %d places down the left fork ",philo->i + 1);
	pthread_mutex_unlock(&philo->set->mutex[(philo->i + 1) % philo->nb]);
	printf("\nPhilosopher % d places down the right fork ",philo->i + 1);
	sleeping(philo);
}
void philosophers(t_philo arg)
{
	pthread_t *t;
    int i;
	t_philo *philo;
	t_philo *head;
	t_inside *tools;

	tools = malloc(sizeof(tools) * 3);
	tools->mutex = malloc(sizeof(pthread_mutex_t) * arg.nb + 1);
	t = malloc(sizeof(pthread_t) * arg.nb + 1);
	pthread_mutex_init(&tools->dead, NULL);
	philo = malloc(sizeof(t_philo) * 9);
	philo = NULL;
	i = 0;
	while(i < arg.nb)
	{
		pthread_mutex_init(&tools->mutex[i], NULL);
		i++;
	}
	i = arg.nb - 1;
	while(0 <= i)
	{
		head = malloc(sizeof(t_philo) * 9);
		head->time_beg = arg.time_beg;
		head->set = malloc(sizeof(head->set) * 3);
		head->nb = arg.nb;
    	head->nb_of_forks = arg.nb;
		head->time_start = arg.time_start;
    	head->time_to_die = arg.time_to_die;
    	head->time_to_eat = arg.time_to_eat;
    	head->time_to_sleep = arg.time_to_sleep;
    	head->nb_of_eat = arg.nb_of_eat;
		head->set = tools;
		head->next = philo;
		philo = head;
		i--;
	}
	i = 0;
	
		i = 0;
	while(1)
	{
		i = 0;
		head = philo;
		while(i < arg.nb)
		{
			head->i = i;
			pthread_create(&t[i],NULL, (void *) routine, head);
			usleep(60);
				check_death(head); 
			head = head->next;
			i+=2;
		}
		i = 1;
		while(i < arg.nb)
		{
			head->i = i;
			pthread_create(&t[i],NULL, (void *) routine, head);
			usleep(60);
			check_death(head); 
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
		pthread_mutex_destroy(&tools->mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&tools->dead);
}

int main(int argc,char **argv)
{
    t_philo arg;
	if(argc == 5)
	{
		arg.time_beg = get_time_now();
    	arg.nb = atoi(argv[1]);
		arg.time_start = get_time_now();
    	arg.nb_of_forks = arg.nb;
    	arg.time_to_die = atoi(argv[2]);
    	arg.time_to_eat = atoi(argv[3]);
    	arg.time_to_sleep = atoi(argv[4]);
		philosophers(arg);
	}
}