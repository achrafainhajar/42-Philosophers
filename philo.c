/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:54:54 by aainhaja          #+#    #+#             */
/*   Updated: 2022/10/08 19:19:49 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time_now(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
void check_death(t_philo *arg)
{	
	int	i;
	i = get_time_now();
	if (i - arg->time_start > arg->time_to_die)
	{
		pthread_mutex_lock(&arg->set->dead);
		exit(1);
	}
	else
	{
		if (arg->nb_of_eat != -1)
		{
			if (arg->k[0] == 0)
			{
				exit(0);
			}
		}
		pthread_mutex_unlock(&arg->set->dead);
	}
}

void eating(t_philo *philo)
{
	long start;
	start = get_time_now();
	ft_print("", philo, " is eating\n");
	philo->time_start = get_time_now();
	while (get_time_now() - start < philo->time_to_eat)
	{
		usleep(100);
	}
}

void sleeping(t_philo *philo)
{
	long i;
	ft_print("", philo, " is sleeping\n");
	i = get_time_now();
	while (get_time_now() - i < philo->time_to_sleep)
	{
		usleep(100);
	}
	ft_print("", philo, " is thinking\n");
}

void routine(void *arg)
{
	t_philo *philo;
	philo = arg;
	while(1)
	{
		if(philo->nb_of_eat == 0)
		{
			while(1);
		}
		pthread_mutex_lock(&philo->set->mutex[philo->i]);
		ft_print("",philo," has taken a fork\n");
		pthread_mutex_lock(&philo->set->mutex[(philo->i + 1) % philo->nb]);
		ft_print("",philo," has taken a fork\n");
		eating(philo);
		if(philo->nb_of_eat > 0)
		{
			philo->nb_of_eat--;
			philo->k[0]--;
		}
		pthread_mutex_unlock(&philo->set->mutex[philo->i]);
		//ft_print("Philosopher ",philo," places down the left fork \n");
		pthread_mutex_unlock(&philo->set->mutex[(philo->i + 1) % philo->nb]);
		//ft_print("Philosopher ",philo," places down the right fork \n");
		sleeping(philo);
	}
}
void philosophers(t_philo arg)
{
	pthread_t *t = NULL;
    int i;
	int *all;
	all = malloc(sizeof(int));
	t_philo *philo = NULL;
	t_philo *head = NULL;
	t_inside *tools = NULL;

	if(arg.nb_of_eat != -1)
	{
		all[0] = (arg.nb * arg.nb_of_eat);
	}
	tools = malloc(sizeof(t_inside));
	tools->mutex = malloc(sizeof(pthread_mutex_t) * arg.nb);
	t = malloc(sizeof(pthread_t) * arg.nb);
	pthread_mutex_init(&tools->dead, NULL);
	pthread_mutex_init(&tools->write, NULL);
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
		head = (t_philo *) malloc(sizeof(t_philo));
		head->time_beg = arg.time_beg;
		head->nb = arg.nb;
		head->k = all;
    	head->nb_of_forks = arg.nb;
		head->time_beg = arg.time_beg;
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
	head = philo;
	i = 1;
	while (1)
	{
		check_death(head);
		if(i == head->nb)
		{
			i = 1;
			head = philo;
			continue;
		}
		head = head->next;
		i++;
	}
}

int main(int argc,char **argv)
{
    t_philo arg;
	if(argc == 5 || argc == 6)
	{
		arg.time_beg = get_time_now();
    	arg.nb = atoi(argv[1]);
		arg.time_start = get_time_now();
    	arg.nb_of_forks = arg.nb;
    	arg.time_to_die = atoi(argv[2]);
    	arg.time_to_eat = atoi(argv[3]);
    	arg.time_to_sleep = atoi(argv[4]);
		if(argc == 5)
			arg.nb_of_eat = -1;
		else
			arg.nb_of_eat = atoi(argv[5]);
		philosophers(arg);
	}
}