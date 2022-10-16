/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:42:14 by aainhaja          #+#    #+#             */
/*   Updated: 2022/10/16 23:17:25 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"
#include <semaphore.h>

void *check_death(t_philo *arg)
{	
	long	i;
	while(arg->set->dead)
	{
		i = get_time_now();
		usleep(100);
		sem_wait(arg->set->d);
		if (i - arg->time_start > arg->time_to_die)
		{
			sem_wait(arg->set->write);
			printf("%ld %d%s",(get_time_now() - arg->time_beg),arg->i + 1," Died\n");
			arg->set->dead = 0;
			break;
		}
		else
		{
			if (arg->nb_of_eat == 0)
			{
				return(NULL);
			}
			sem_post(arg->set->d);
		}
	}
	exit(1);
}

void ft_print(char *s1,t_philo *head,char *s2)
{
	sem_wait(head->set->write);
    	printf("%ld %s%d%s",(get_time_now() - head->time_beg),s1,head->i + 1,s2);
	sem_post(head->set->write);
}

long get_time_now(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


void eating(t_philo *philo)
{
	sem_wait(philo->set->eat);
	if(philo->nb_of_eat > 0)
		philo->nb_of_eat--;
	long start;
	start = get_time_now();
	philo->time_start = get_time_now();
	sem_post(philo->set->eat);
	ft_print("", philo, " is eating\n");
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
	while(philo->nb_of_eat != 0)
	{
		if(philo->i % 2)
			usleep(1500);
		sem_wait(philo->set->sem);
		pthread_create(&philo->set->death,NULL,(void *)check_death,philo);
		ft_print("",philo," has taken a fork\n");
		sem_wait(philo->set->sem);
		ft_print("",philo," has taken a fork\n");
		eating(philo);
		sem_post(philo->set->sem);
		sem_post(philo->set->sem);
		sleeping(philo);
	}
}

void philosophers1(t_philo arg)
{
    int pid;
    int i;
	int *all;

	all = malloc(sizeof(int));
	t_inside *tools= NULL;
    i = 0;
	if(arg.nb_of_eat != -1)
	{
		all[0] = (arg.nb * arg.nb_of_eat);
	}
	tools = malloc(sizeof(t_inside));
	sem_unlink("forks");
	sem_unlink("eat");
	sem_unlink("d");
	sem_unlink("write");
	sem_unlink("time");
   	tools->sem = sem_open("forks", O_CREAT, 0600, arg.nb);
	tools->d = sem_open("d", O_CREAT, 0600, 1);
	tools->eat = sem_open("eat", O_CREAT, 0600, 1);
	tools->write = sem_open("write", O_CREAT, 0600, 1);
	pthread_t *t;
    i = arg.nb - 1;
    t_philo *head = NULL;
    t_philo *philo = NULL;
    while(0 <= i)
	{
		head = (t_philo *) malloc(sizeof(t_philo));
		head->time_beg = arg.time_beg;
		head->nb = arg.nb;
		head->time_beg = arg.time_beg;
		head->k = all;
		head->time_start = arg.time_start;
    	head->time_to_die = arg.time_to_die;
    	head->time_to_eat = arg.time_to_eat;
    	head->time_to_sleep = arg.time_to_sleep;
    	head->nb_of_eat = arg.nb_of_eat;
		head->set = tools;
		head->next = philo;
		head->set->dead = 1;
		philo = head;
		i--;
	}
	head = philo;
    i = 0;
    while(i < arg.nb)
    {
        head->pid = fork();
        if(head->pid == 0)
        {
			head->i = i;
			routine(head);
			exit(0);
        }
		head = head->next;
        i++;
    }
	head = philo;
	int status;
	while(wait(&status) > 0)
	{
		if(WEXITSTATUS(status) == 1)
		{
			while(head)
			{
				kill(head->pid,SIGKILL);
				head = head->next;
			}
		}
	}

}

int main(int argc,char **argv)
{
    t_philo arg;

	if(argc == 5 || argc == 6)
	{
		arg.time_beg = get_time_now();;
    	arg.nb = atoi(argv[1]);
		arg.time_start = get_time_now();
    	arg.time_to_die = atoi(argv[2]);
    	arg.time_to_eat = atoi(argv[3]);
    	arg.time_to_sleep = atoi(argv[4]);
		if(argc == 5)
			arg.nb_of_eat = -1;
		else
			arg.nb_of_eat = atoi(argv[5]);
		philosophers1(arg);
	}
}