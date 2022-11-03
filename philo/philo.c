/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:54:54 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/04 00:14:00 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_philo *arg)
{	
	long	i;

	i = get_time_now();
	pthread_mutex_lock(&arg->set->eat);
	if (i - arg->time_start >= arg->time_to_die)
	{
		pthread_mutex_lock(&arg->set->dead);
		pthread_mutex_lock(&arg->set->write);
		printf("%ld %d%s", (i - arg->time_beg),
			arg->i + 1, " Died\n");
		arg->set->death = 0;
	}
	else
	{
		if (arg->nb_of_eat != -1)
		{
			if (arg->k[0] == 0)
				arg->set->eated = 0;
		}
		pthread_mutex_unlock(&arg->set->eat);
	}
}

void	eating(t_philo *philo)
{
	long	start;

	pthread_mutex_lock(&philo->set->eat);
	if (philo->nb_of_eat > 0)
	{
		philo->nb_of_eat--;
		philo->k[0]--;
	}
	start = get_time_now();
	philo->time_start = get_time_now();
	pthread_mutex_unlock(&philo->set->eat);
	ft_print("", philo, " is eating\n");
	while (get_time_now() - start < philo->time_to_eat)
	{
		usleep(100);
	}
}

void	sleeping(t_philo *philo)
{
	long	i;

	ft_print("", philo, " is sleeping\n");
	i = get_time_now();
	while (get_time_now() - i < philo->time_to_sleep)
	{
		usleep(100);
	}
	ft_print("", philo, " is thinking\n");
	if (philo->nb_of_eat == 0)
		philo->nb_of_eat = -2;
}

void	routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (philo->set->eated)
	{
		pthread_mutex_lock(&philo->set->dead);
		if (philo->set->death == 0)
			break ;
		pthread_mutex_unlock(&philo->set->dead);
		if (philo->i % 2)
			usleep(100);
		pthread_mutex_lock(&philo->set->mutex[philo->i]);
		ft_print("", philo, " has taken a fork\n");
		pthread_mutex_lock(&philo->set->mutex[(philo->i + 1) % philo->nb]);
		ft_print("", philo, " has taken a fork\n");
		eating(philo);
		pthread_mutex_unlock(&philo->set->mutex[philo->i]);
		pthread_mutex_unlock(&philo->set->mutex[(philo->i + 1) % philo->nb]);
		sleeping(philo);
	}
}

int	main(int argc, char **argv)
{
	t_philo	arg;

	if (argc == 5 || argc == 6)
	{
		if (!ft_check_arg(argv))
		{
			return (1);
		}
		arg.time_beg = get_time_now();
		arg.nb = ft_atoi(argv[1]);
		arg.time_start = get_time_now();
		arg.time_to_die = ft_atoi(argv[2]);
		arg.time_to_eat = ft_atoi(argv[3]);
		arg.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 5)
			arg.nb_of_eat = -1;
		else
			arg.nb_of_eat = ft_atoi(argv[5]);
		if (ft_check(arg, argc))
			philosophers(arg);
	}
	else
		ft_putstr_fd("Too many or few arguments\n", 2);
}
