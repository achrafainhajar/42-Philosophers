/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:42:14 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/02 12:06:53 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"
#include <semaphore.h>

void	eating(t_philo *philo)
{
	long	start;

	sem_wait(philo->set->eat);
	philo->eated = 1;
	ft_print("", philo, " is eating\n");
	if (philo->nb_of_eat > 0)
		philo->nb_of_eat--;
	gettimeofday(&philo->time_start, NULL);
	start = philo->time_start.tv_sec * 1000 + philo->time_start.tv_usec / 1000;
	sem_post(philo->set->eat);
	while (get_time_now() - start < philo->time_to_eat)
		usleep(100);
	philo->eated = 0;
}

void	sleeping(t_philo *philo)
{
	long	i;

	i = get_time_now();
	ft_print("", philo, " is sleeping\n");
	while (get_time_now() - i < philo->time_to_sleep)
		usleep(100);
	ft_print("", philo, " is thinking\n");
}

void	routine(void *arg)
{
	t_philo		*philo;

	philo = arg;
	pthread_create(&philo->set->death, NULL, (void *)check_death, philo);
	while (philo->nb_of_eat != 0)
	{
		if (philo->i % 2)
			usleep(100);
		sem_wait(philo->set->sem);
		ft_print("", philo, " has taken a fork\n");
		sem_wait(philo->set->sem);
		ft_print("", philo, " has taken a fork\n");
		eating(philo);
		sem_post(philo->set->sem);
		sem_post(philo->set->sem);
		sleeping(philo);
	}
}

int	main(int argc, char **argv)
{
	t_philo	arg;

	if (argc == 5 || argc == 6)
	{
		if (!ft_check_arg(argv))
			return (1);
		arg.time_beg = get_time_now();
		arg.nb = ft_atoi(argv[1]);
		gettimeofday(&arg.time_start, NULL);
		arg.time_to_die = ft_atoi(argv[2]);
		arg.time_to_eat = ft_atoi(argv[3]);
		arg.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 5)
			arg.nb_of_eat = -1;
		else
			arg.nb_of_eat = ft_atoi(argv[5]);
		if (ft_check(arg, argc))
			philosophers1(arg);
	}
	else
		ft_putstr_fd("Too many or few arguments\n", 2);
}
