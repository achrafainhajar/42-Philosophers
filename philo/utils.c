/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:07:47 by aainhaja          #+#    #+#             */
/*   Updated: 2022/10/30 09:07:47 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(char *s1, t_philo *head, char *s2)
{
	pthread_mutex_lock(&head->set->write);
	if (head->nb_of_eat != -2)
		printf("%ld %s%d%s", (get_time_now() - head->time_beg),
			s1, head->i + 1, s2);
	pthread_mutex_unlock(&head->set->write);
}

long	get_time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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

int	ft_check_arg(char **str)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (str[j])
	{
		i = 0;
		while (str[j][i])
		{
			if (!(str[j][i] <= '9' && str[j][i] >= '0'))
			{
				ft_putstr_fd("Bad arguments\n", 2);
				return (0);
			}
			i++;
		}
		j++;
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
