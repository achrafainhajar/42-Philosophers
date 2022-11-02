/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:48:16 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/02 12:08:56 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*create_philos(t_philo arg, t_inside *tools, int i, int *all)
{	
	t_philo	*head;
	t_philo	*philo;

	while (0 <= i--)
	{
		head = (t_philo *) malloc(sizeof(t_philo));
		if (head == NULL)
			return (NULL);
		head->time_beg = arg.time_beg;
		head->nb = arg.nb;
		head->k = all;
		head->time_start = arg.time_start;
		head->time_to_die = arg.time_to_die;
		head->time_to_eat = arg.time_to_eat;
		head->time_to_sleep = arg.time_to_sleep;
		head->nb_of_eat = arg.nb_of_eat;
		head->set = tools;
		head->next = philo;
		head->set->eat = 0;
		head->set->dead = 1;
		philo = head;
	}
	return (philo);
}

t_inside	*create_sem(t_inside *tools, t_philo arg)
{
	tools = malloc(sizeof(t_inside));
	sem_unlink("forks");
	sem_unlink("eat");
	sem_unlink("d");
	sem_unlink("write");
	tools->sem = sem_open("forks", O_CREAT, 0600, arg.nb);
	tools->d = sem_open("d", O_CREAT, 0600, 1);
	tools->eat = sem_open("eat", O_CREAT, 0600, 1);
	tools->write = sem_open("write", O_CREAT, 0600, 1);
	return (tools);
}

void	w_process(t_philo *head)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WEXITSTATUS(status) == 1)
		{
			while (head)
			{
				kill(head->pid, SIGKILL);
				head = head->next;
			}
		}
	}
}

void	ft_supervisor(t_philo *head, t_philo arg)
{
	int	i;

	i = 0;
	while (i < arg.nb)
	{
		head->pid = fork();
		if (head->pid == 0)
		{
			head->i = i;
			routine(head);
			exit(0);
		}
		head = head->next;
		i++;
	}
}

void	philosophers1(t_philo	arg)
{
	t_inside	*tools;
	t_philo		*philo;
	int			*all;

	all = malloc(sizeof(int));
	if (all == NULL)
		return ;
	if (arg.nb_of_eat != -1)
		all[0] = (arg.nb * arg.nb_of_eat);
	philo = NULL;
	tools = NULL;
	tools = create_sem(tools, arg);
	philo = create_philos(arg, tools, arg.nb - 1, all);
	ft_supervisor(philo, arg);
	w_process(philo);
}
