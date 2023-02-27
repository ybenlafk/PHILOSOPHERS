/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:01:19 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/02/26 23:48:03 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	the_rest(t_philo *philos)
{
	pthread_mutex_lock(&philos->vars->lock);
	printf("%lld %d is sleeping\n", get_time() - philos->vars->time, philos->id);
	ft_usleep(philos->src->time_to_sleep); 
	philos->ok = 0;
	if (philos->is)
		pthread_mutex_unlock(&philos->vars->lock);
	pthread_mutex_lock(&philos->vars->lock);
	printf("%lld %d is thinking\n", get_time() - philos->vars->time, philos->id);
	if (philos->is)
		pthread_mutex_unlock(&philos->vars->lock);
}

void	lock_forks(t_philo *philos)
{
	pthread_mutex_lock(philos->fork_one);
	pthread_mutex_lock(philos->fork_two);
	pthread_mutex_lock(&philos->vars->lock);
	printf("%lld %d has taken a fork\n",
		get_time() - philos->vars->time, philos->id);
	printf("%lld %d has taken a fork\n",
		get_time() - philos->vars->time, philos->id);
	pthread_mutex_unlock(&philos->vars->lock);
}

void	unlock_forks(t_philo *philos)
{
	pthread_mutex_lock(&philos->vars->lock);
	printf("%lld %d is eating\n", get_time() - philos->vars->time, philos->id);
	philos->ok = 1;
	pthread_mutex_unlock(&philos->vars->lock);
	philos->time_after_eat = get_time();
	ft_usleep(philos->src->time_to_eat);
	pthread_mutex_unlock(philos->fork_one);
	pthread_mutex_unlock(philos->fork_two);
}

void	*routine(void *param)
{
	t_philo	*philos;

	if (!param)
		return (NULL);
	philos = (t_philo *)param;
	while (philos->is)
	{
		if (!(philos->id % 2))
			usleep(100);
		lock_forks(philos);
		unlock_forks(philos);
		if (philos->eat_mode)
		{
			pthread_mutex_lock(&philos->vars->lock);
			philos->eat_count++;
			if (philos->eat_count == philos->src->times_philos_must_eat)
			philos->vars->rep++;
			pthread_mutex_unlock(&philos->vars->lock);
		}
		the_rest(philos);
	}
	return (NULL);
}
