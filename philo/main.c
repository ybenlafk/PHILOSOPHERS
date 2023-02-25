/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:20:12 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/02/25 18:45:14 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int main(int ac, char **av)
{
    t_var vars;
    t_src   src;
    philo philos[10000];


    vars.i = 0;
    vars.time = get_time();
    if (parsing(ac, av, &src))
        return (printf("Bad arguments\n"), 1);
    if (src.philos_nb <= 1)
    {
        usleep(src.time_to_die * 1000);
        printf("%lld %d died\n", get_time() - vars.time, 1);
        return (0);
    }
    while (vars.i < src.philos_nb)
        pthread_mutex_init(&src.forks[vars.i++], NULL);
	pthread_mutex_init(&vars.lock, NULL);
	pthread_mutex_init(&vars.ls, NULL);
    if (src.len == 4)
	    fill_philos(&src, philos, &vars, 0);
    else
        fill_philos(&src, philos, &vars, 1);
    while (philos->j)
    {
        pthread_mutex_lock(&philos->vars->lock);
        if (is_death(philos, &src))
        {
            philos->j = 0;
            printf("%lld %d died\n", get_time() - philos->vars->time, philos->id);
            break;
        }
        if (philos->rep >= src.philos_nb && philos->eat_mode)
        {
            philos->j = 0;
            break;
        }
        pthread_mutex_unlock(&philos->vars->lock);
    }
    vars.i = 0;
    while (vars.i < src.philos_nb)
        pthread_detach(philos[vars.i++].thd);
    
    vars.i = 0;
     while (vars.i < src.philos_nb)
        pthread_mutex_destroy(&src.forks[vars.i++]);
    return (0);
}