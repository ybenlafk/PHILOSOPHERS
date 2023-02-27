/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:20:12 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/02/26 23:41:05 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy(t_src *src, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < src->philos_nb)
		pthread_detach(philos[i++].thd);
	i = 0;
	while (i < src->philos_nb)
		pthread_mutex_destroy(&src->forks[i++]);
}

void	threads_creator(t_src *src, t_philo *philos, t_var *vars)
{
	while (vars->i < src->philos_nb)
		pthread_mutex_init (&src->forks[vars->i++], NULL);
	pthread_mutex_init(&vars->lock, NULL);
	if (src->len == 4)
		fill_philos(src, philos, vars, 0);
	else
		fill_philos(src, philos, vars, 1);
	while (philos->is)
	{
		pthread_mutex_lock(&philos->vars->lock);
		if (is_death(philos, src))
		{
			philos->is = 0;
			break ;
		}
		if (philos->vars->rep >= src->philos_nb && philos->eat_mode)
		{
			philos->is = 0;
			break ;
		}
		pthread_mutex_unlock(&philos->vars->lock);
	}
}

int	main(int ac, char **av)
{
	t_var	vars;
	t_src	src;
	t_philo	philos[10000];

	vars.i = 0;
	vars.rep = 0;
	vars.time = get_time();
	if (parsing(ac, av, &src))
		return (printf("Bad arguments\n"), 1);
	if (src.philos_nb <= 1)
	{
		usleep(src.time_to_die * 1000);
		printf("%lld %d died\n", get_time() - vars.time, 1);
		return (0);
	}
	threads_creator(&src, philos, &vars);
	ft_destroy(&src, philos);
	return (0);
}
