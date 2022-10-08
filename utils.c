#include"philo.h"
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(1, &s[i], 1);
			i++;
		}
	}
}

void	ft_putnbr(int n)
{
	long	nb;

	nb = (long) n;
	if (nb < 0)
	{
		nb = nb * -1;
		ft_putchar('-');
	}
	if (nb < 10)
	{
		ft_putchar(nb + 48);
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}
void ft_print(char *s1,t_philo *head,char *s2)
{
    pthread_mutex_lock(&head->set->write);
    printf("%ld %s%d%s",(get_time_now() - head->time_beg),s1,head->i + 1,s2);
	if(head->set->death == 1)
    	pthread_mutex_unlock(&head->set->write);
}