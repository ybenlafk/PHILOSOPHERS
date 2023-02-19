/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:20:12 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/02/19 16:26:07 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int main(int ac, char **av)
{
    t_var vars;
    t_src   src;
    philo philos[10000];
    int i = 0;

    vars.time = get_time();
    
    if (parsing(ac, av, &src))
        return (printf("Bad arguments\n"), 1);
    while (i < src.philos_nb)
        pthread_mutex_init(&src.forks[i++], NULL);
	fill_philos(&src, philos, &vars);
    i = 0;
    while (i < src.philos_nb)
        pthread_join(src.threads[i++], NULL);
    i = 0;
     while (i < src.philos_nb)
        pthread_mutex_destroy(&src.forks[i++]);
    
    // printf("%d\n", src.philos_nb);
    // printf("%lld\n", src.time_to_die);
    // printf("%lld\n", src.time_to_eat);
    // printf("%lld\n", src.time_to_sleep);
    // printf("%lld\n", src.times_philos_must_eat);
    // printf("%lld\n", get_time());
    // int i;

	// i = 0;
	// while (i < src.philos_nb)
	// {
    //     printf("%d\n", philos[i].id);
    //     printf("%d\n", philos[i].die);
    //     printf("left %d\n", philos[i].left_fork);
    //     printf("right %d\n", philos[i].right_fork);
    //     i++;
	// }
}