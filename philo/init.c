/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:32:34 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/01 08:44:51 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_philo	*create_philos(t_philo *philo, t_philo arg, t_inside *tools, int i)
{	
	t_philo	*head;
	int		*all;

	all = NULL;
	all = malloc(sizeof(int));
	if (arg.nb_of_eat != -1)
		all[0] = (arg.nb * arg.nb_of_eat);
	while (0 <= i)
	{
		head = (t_philo *) malloc(sizeof(t_philo));
		head->time_beg = arg.time_beg;
		head->nb = arg.nb;
		head->k = all;
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
	return (philo);
}

t_inside	*create_mutexes(t_philo arg)
{
	int			i;
	t_inside	*tools;

	tools = NULL;
	tools = malloc(sizeof(t_inside));
	tools->mutex = malloc(sizeof(pthread_mutex_t) * arg.nb);
	tools->death = 1;
	tools->eated = 1;
	tools->rc = malloc(sizeof(pthread_mutex_t) * arg.nb);
	pthread_mutex_init(&tools->dead, NULL);
	pthread_mutex_init(&tools->eat, NULL);
	pthread_mutex_init(&tools->write, NULL);
	pthread_mutex_init(&tools->time, NULL);
	i = 0;
	while (i < arg.nb)
	{
		pthread_mutex_init(&tools->mutex[i], NULL);
		pthread_mutex_init(&tools->rc[i], NULL);
		i++;
	}
	return (tools);
}

void	ft_philoos(t_philo *head, pthread_t *t, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		head->i = i;
		pthread_create(&t[i], NULL, (void *) routine, head);
		head = head->next;
		i += 2;
	}
	i = 1;
	while (i < nb)
	{
		head->i = i;
		pthread_create(&t[i], NULL, (void *) routine, head);
		head = head->next;
		i += 2;
	}
}

void	philosophers(t_philo arg)
{
	pthread_t	*t;
	int			i;
	t_philo		*philo;
	t_philo		*head;
	t_inside	*tools;

	philo = NULL;
	t = malloc(sizeof(pthread_t) * arg.nb);
	tools = create_mutexes(arg);
	philo = create_philos(philo, arg, tools, arg.nb - 1);
	ft_philoos(philo, t, arg.nb);
	head = philo;
	i = 1;
	while (head->set->eated && head->set->death)
	{
		check_death(head);
		if (i == head->nb)
		{
			i = 1;
			head = philo;
			continue ;
		}
		head = head->next;
		i++;
	}
}
