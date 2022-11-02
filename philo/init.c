/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:32:34 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/02 08:29:26 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_philo	*create_philos(t_philo arg, t_inside *tools, int i, int *all)
{	
	t_philo	*head;
	t_philo	*philo;

	while (0 <= i)
	{
		head = (t_philo *) malloc(sizeof(t_philo));
		if (head == NULL)
			return (NULL);
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
	if (tools == NULL)
		return (NULL);
	tools->mutex = malloc(sizeof(pthread_mutex_t) * arg.nb);
	if (tools->mutex == NULL)
		return (NULL);
	tools->death = 1;
	tools->eated = 1;
	pthread_mutex_init(&tools->dead, NULL);
	pthread_mutex_init(&tools->eat, NULL);
	pthread_mutex_init(&tools->write, NULL);
	pthread_mutex_init(&tools->time, NULL);
	i = 0;
	while (i < arg.nb)
	{
		pthread_mutex_init(&tools->mutex[i], NULL);
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

void	ft_supervisor(t_philo *philo)
{
	t_philo	*head;
	int		i;

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

void	philosophers(t_philo arg)
{
	pthread_t	*t;
	t_philo		*philo;
	t_inside	*tools;
	int			*all;

	all = NULL;
	all = malloc(sizeof(int));
	if (all == NULL)
		return ;
	if (arg.nb_of_eat != -1)
		all[0] = (arg.nb * arg.nb_of_eat);
	t = malloc(sizeof(pthread_t) * arg.nb);
	if (t == NULL)
		return ;
	tools = create_mutexes(arg);
	philo = create_philos(arg, tools, arg.nb - 1, all);
	ft_philoos(philo, t, arg.nb);
	ft_supervisor(philo);
	free(t);
}

int	ft_atoi(const char	*str)
{
	unsigned long long	i;
	unsigned long long	b;
	long				l;

	l = 1;
	i = 0;
	b = 0;
	while ((str[i] >= 7 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			l = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		b = b * 10 + (str[i++] - '0');
	if (l == -1 && b >= 9223372036854775807)
		return (0);
	if (b >= 9223372036854775807)
		return (-1);
	return ((long)l * b);
}
