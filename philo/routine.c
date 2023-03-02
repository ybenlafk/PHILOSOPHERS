/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:01:19 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/02 14:09:27 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	writeline(t_philo *philos, char *s)
{
	pthread_mutex_t	lock;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&philos->vars->lock);
	printf("%lld %d %s\n",
		get_time() - philos->vars->time, philos->id, s);
	pthread_mutex_unlock(&philos->vars->lock);
	pthread_mutex_destroy(&lock);
}

void	locked_msg(t_philo *philos, int stat)
{	
	if (!stat)
		writeline(philos, "has taken a fork");
	else if (stat == 1)
	{
		writeline(philos, "is eating");
		pthread_mutex_lock(&philos->vars->lock);
		philos->time_after_eat = get_time();
		pthread_mutex_unlock(&philos->vars->lock);
	}
	else if (stat == 2)
		writeline(philos, "is sleeping");
	else if (stat == 3)
		writeline(philos, "is thinking");
}

void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	locked_msg(philo, 0);
	pthread_mutex_lock(&philo->next->fork);
	locked_msg(philo, 0);
}

void	unlock_forks(t_philo *philo)
{
	if (philo->ok)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
}

void	*routine(void *param)
{
	t_philo	*philos;

	if (!param)
		return (NULL);
	philos = (t_philo *)param;
	pthread_mutex_lock(&philos->vars->lss);
	while (philos->ok)
	{
		pthread_mutex_unlock(&philos->vars->lss);
		if (!(philos->id % 2))
			usleep(100);
		lock_forks(philos);
		locked_msg(philos, 1);
		ft_usleep(philos->src->time_to_eat);
		unlock_forks(philos);
		eat_counter(philos);
		locked_msg(philos, 2);
		ft_usleep(philos->src->time_to_sleep);
		locked_msg(philos, 3);
	}
	return (NULL);
}
