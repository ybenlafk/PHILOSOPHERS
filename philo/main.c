/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:20:12 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/08 11:36:20 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy(t_philo *philos, t_src *src, t_var *vars)
{
	int	i;

	i = 0;
	while (i < src->philos_nb)
		pthread_detach(vars->threads[i++]);
	i = 0;
	while (i < src->philos_nb)
	{
	    pthread_mutex_destroy(&philos->fork);
	    philos = philos->next;
	    i++;
	    if (philos == NULL)
	        break;
	}
	pthread_mutex_destroy(&vars->lock);
	pthread_mutex_destroy(&vars->ls);
	pthread_mutex_destroy(&vars->lss);
}

// void	print_dead(t_philo *philos, t_var *vars)
// {
// 	pthread_mutex_lock(&philos->vars->lock);
// 	printf("%lld %d died\n",
// 				get_time() - philos->vars->time, philos->id);
// 	pthread_mutex_unlock(&philos->vars->lock);
// }
void	checker(t_src *src, t_philo *philos, t_var *vars)
{
	while (1)
	{
		pthread_mutex_lock(&vars->ls);
		if ((get_time() - philos->time_after_eat) > src->time_to_die)
		{
			while(philos->ok)
			{
				pthread_mutex_lock(&philos->vars->lock);
				philos->ok = 0;
				pthread_mutex_unlock(&philos->vars->lock);
				philos = philos->next;
			}
			pthread_mutex_unlock(&vars->ls);
			// print_dead(philos, vars);
			ft_destroy(philos, src, vars);
			list_free(&philos, src->philos_nb);
			return ;
		}
		if (philos->vars->rep >= src->philos_nb && philos->eat_mode)
		{
			philos->ok = 0;
			pthread_mutex_unlock(&vars->ls);
			ft_destroy(philos, src, vars);
			list_free(&philos, src->philos_nb);
			return ;
		}
		pthread_mutex_unlock(&vars->ls);
		philos = philos->next;
	}
}

void	threads_creator(t_src *src, t_philo *philos, t_var *vars)
{
	int	i;

	i = 0;
	pthread_mutex_init(&vars->lock, NULL);
	pthread_mutex_init(&vars->ls, NULL);
	pthread_mutex_init(&vars->lss, NULL);
	if (src->len == 4)
		fill_philos(src, &philos, vars, 0);
	else
		fill_philos(src, &philos, vars, 1);
	created_philos(philos, src, vars);
	checker(src, philos, vars);
	while (i < src->philos_nb)
		pthread_detach(vars->threads[i++]);
}

int	main(int ac, char **av)
{
	t_var	vars;
	t_src	src;
	t_philo	*philos;

	if (ac == 1)
		return (0);
	vars.i = 0;
	vars.rep = 0;
	vars.ok = 1;
	vars.time = get_time();
	philos = NULL;
	if (parsing(ac, av, &src))
		return (printf("Bad arguments\n"), 1);
	threads_creator(&src, philos, &vars);
	return (0);
}
