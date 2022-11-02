/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:59:46 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/02 08:01:10 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h> 
# include <unistd.h>
# include <semaphore.h>

typedef struct s_inside
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	dead;
	pthread_mutex_t	write;
	pthread_mutex_t	time;
	pthread_mutex_t	eat;
	int				death;
	int				eated;
}	t_inside;

typedef struct s_philo {
	int				nb;
	int				i;
	long			time_beg;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				nb_of_eat;
	long			time_start;
	int				*k;
	t_inside		*set;
	struct s_philo	*next;
}			t_philo;

void		ft_putstr(char *s);
void		ft_putchar(char c);
void		ft_putnbr(int n);
long		get_time_now(void);
void		ft_print(char *s1, t_philo *head, char *s2);
t_philo		*create_philos(t_philo arg, t_inside *tools, int i, int *all);
void		ft_philoos(t_philo *head, pthread_t *t, int nb);
void		philosophers(t_philo arg);
void		routine(void *arg);
void		check_death(t_philo *arg);
int			ft_check(t_philo philo, int argc);
void		ft_putstr_fd(char *s, int fd);
int			ft_check_arg(char **str);
int			ft_atoi(const char	*str);
#endif
