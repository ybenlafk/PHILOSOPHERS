/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 21:15:04 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/02 14:10:44 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	src_init(t_src *src, t_var *p)
{
	src->time_to_die = ft_atoi(p->str[1]);
	src->time_to_eat = ft_atoi(p->str[2]);
	src->time_to_sleep = ft_atoi(p->str[3]);
	if (src->len == 5)
	{
		src->times_philos_must_eat = ft_atoi(p->str[4]);
		if (src->times_philos_must_eat <= 0)
			return (1);
	}
	return (0);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep (150);
}

void	created_philos(t_philo *philo, t_src *src, t_var *vars)
{
	int	i;

	vars->time = get_time();
	i = 0;
	while (i < src->philos_nb)
	{
		if (pthread_create(&vars->threads, NULL, routine, philo))
			return ;
		usleep(10);
		i++;
		philo = philo->next;
	}
}

void	list_free(t_philo **philos, int len)
{
	t_philo	*tmp;

	while (len--)
	{
		tmp = (*philos);
		*philos = (*philos)->next;
		free(tmp);
	}
}

void	eat_counter(t_philo *philos)
{
	if (philos->eat_mode)
	{
		pthread_mutex_lock(&philos->vars->lock);
		philos->eat_count++;
		if (philos->eat_count == philos->src->times_philos_must_eat)
			philos->vars->rep++;
		pthread_mutex_unlock(&philos->vars->lock);
	}
}
