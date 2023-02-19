/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:01:19 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/02/19 16:38:05 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine(void *param)
{
  int i;
  int j;
  long long tm[10000];
  philo *philos = (philo *)param;
  j = 1;
  while (j)
  {
    i = 0;
    if (!(philos->id % 2))
      usleep(100000);
    pthread_mutex_lock(philos->fork_one);
    pthread_mutex_lock(philos->fork_two);
    printf("%lld %d has taken a fork\n", get_time() - philos->src->time, philos->id);
    printf("%lld %d has taken a fork\n", get_time() - philos->src->time, philos->id);
    printf("%lld %d is eating\n", get_time() - philos->src->time, philos->id);
    usleep(philos->src->time_to_eat * 1000);
    pthread_mutex_unlock(philos->fork_one);
    pthread_mutex_unlock(philos->fork_two);
    tm[philos->id] = get_time();
    printf("%lld %d is sleeping\n", get_time() - philos->src->time, philos->id);
    usleep(philos->src->time_to_sleep * 1000);
    printf("%lld %d is thinking\n", get_time() - philos->src->time, philos->id);
  }
  return (NULL);
}