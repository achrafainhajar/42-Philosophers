/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:50:14 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/02 08:27:41 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check(t_philo philo, int argc)
{
	if (philo.nb <= 0 || philo.time_to_die < 0
		|| philo.time_to_eat < 0 || philo.time_to_sleep < 0)
	{
		ft_putstr_fd("Bad arguments\n", 2);
		return (0);
	}
	if (argc == 6)
	{
		if (philo.nb_of_eat < 0)
		{
			ft_putstr_fd("Bad arguments\n", 2);
			return (0);
		}
	}
	return (1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

void	ft_print(char *s1, t_philo *head, char *s2)
{
	sem_wait(head->set->write);
	printf("%ld %s%d%s", (get_time_now() - head->time_beg),
		s1, head->i + 1, s2);
	sem_post(head->set->write);
}

long	get_time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*check_death(t_philo	*arg)
{	
	long	i;
	long	b;

	while (1)
	{
		i = get_time_now();
		sem_wait(arg->set->d);
		b = arg->time_start.tv_sec * 1000 + arg->time_start.tv_usec / 1000;
		if ((i - b) > arg->time_to_die && arg->i == 0)
		{
			sem_wait(arg->set->write);
			printf("%ld %d%s", (i - arg->time_beg), arg->i + 1, " Died\n");
			arg->set->dead = 0;
			break ;
		}
		sem_post(arg->set->d);
	}
	exit(1);
}
