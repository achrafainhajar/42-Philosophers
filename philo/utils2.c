/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:10:08 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/02 12:10:26 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

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
