/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:27:29 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/02/26 23:24:59 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	scapes(char *str, int *i)
{
	while (str[*i] == '\t' || str[*i] == '\n'
		|| str[*i] == '\v' || str[*i] == '\f'
		|| str[*i] == '\r' || str[*i] == ' ')
		(*i)++;
}

long long	ft_atoi(char *str)
{
	long long	res;
	int			i;
	int			sign;

	sign = 1;
	i = 0;
	res = 0;
	scapes(str, &i);
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
		res = res * 10 + str[i++] - '0';
	return (res * sign);
}

void	freedom(char **p)
{
	int	i;

	i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		ms;

	if (gettimeofday(&tv, NULL))
		return (-1);
	ms = (long long) tv.tv_sec * 1000 + (long long) tv.tv_usec / 1000;
	return (ms);
}

int	is_death(t_philo *philos, t_src *src)
{
	int	i;

	i = 0;
	while (i < src->philos_nb)
	{
		// printf("%d ======> %lld\n", i,get_time() - philos[i].time_after_eat);
		// usleep(1000);
		if (((get_time()) - philos[i].time_after_eat) >= src->time_to_die
			&& philos[i].ok)
		{
			printf("%lld %d died\n",
				get_time() - philos->vars->time, i);
			return (1);
		}
		i++;
	}
	return (0);
}
