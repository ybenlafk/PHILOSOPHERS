/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:01:19 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/02/25 19:05:20 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void  lock_forks(philo *philos)
{
    pthread_mutex_lock(philos->fork_one);
    pthread_mutex_lock(philos->fork_two);
    
    pthread_mutex_lock(&philos->vars->lock);
    printf("%lld %d has taken a fork\n", get_time() - philos->vars->time, philos->id);
    printf("%lld %d has taken a fork\n", get_time() - philos->vars->time, philos->id);
    pthread_mutex_unlock(&philos->vars->lock);
}

void  unlock_forks(philo *philos)
{
    pthread_mutex_lock(&philos->vars->lock);
    if (philos->eat_mode)
      philos->eat_count++;
    if (philos->eat_count == philos->src->times_philos_must_eat)
      philos->rep++;
    printf("%lld %d is eating\n", get_time() - philos->vars->time, philos->id);
    philos->vars->time_after_eat = get_time();
    pthread_mutex_unlock(&philos->vars->lock);
    usleep(philos->src->time_to_eat * 1000);
    usleep(philos->src->time_to_sleep * 1000);
    pthread_mutex_unlock(philos->fork_one);
    pthread_mutex_unlock(philos->fork_two);
}

void    *routine(void *param)
{
  if (!param)
    return (NULL);
  philo *philos = (philo *)param;
  while (philos->j)
  {
    if (!(philos->id % 2))
      usleep(1000);
    lock_forks(philos);
    // pthread_mutex_lock(&philos->vars->lock);
    unlock_forks(philos);
    // pthread_mutex_unlock(&philos->vars->lock);
   
    pthread_mutex_lock(&philos->vars->lock);
    printf("%lld %d is sleeping\n", get_time() - philos->vars->time, philos->id);
    if(philos->j)
      pthread_mutex_unlock(&philos->vars->lock);
    usleep(philos->src->time_to_sleep * 1000);
    pthread_mutex_lock(&philos->vars->lock);
    printf("%lld %d is thinking\n", get_time() - philos->vars->time, philos->id);
    if(philos->j)
      pthread_mutex_unlock(&philos->vars->lock);
  }

  return (NULL);
}