/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 21:15:04 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/02/26 23:48:23 by ybenlafk         ###   ########.fr       */
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
	long long start;

	start = get_time();
	while (get_time() - start <= time)
		usleep (1000);
}