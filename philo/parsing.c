/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:13:15 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/02/25 18:36:07 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_int(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '-')
			j++;
		while (av[i][j])
		{
			if (!is_digit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	list_len(char **s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	fill_philos(t_src *src, philo *philos, t_var *vars, int stat)
{
	int i;

	i = 0;
	while (i < src->philos_nb)
	{
		philos[i].id = i + 1; 
		philos[i].j = 1;
		philos[i].rep = 0;
		philos[i].fork_one = &src->forks[i];
		philos[i].fork_two = &src->forks[(i + 1) % src->philos_nb];
		philos[i].src = src;
		philos[i].vars = vars;
		philos[i].eat_mode = 0;
		if (stat)
		{
			philos[i].eat_count = 0;
			philos[i].eat_mode = 1;
		}
		pthread_create(&philos[i].thd, NULL, routine, (void *)&philos[i]);
        i++;
	}
}

int	parsing(int ac, char **av, t_src *src)
{
	t_var	p;

	p.i = 0;
	p.s = ft_strjoin(ac - 1, av + 1, " ");
	if (!p.s)
		return (free(p.s), 1);
	p.str = ft_split(p.s, ' ');
	free(p.s);
	if (!is_int(p.str))
		return (freedom(p.str), 1);
	src->len = list_len(p.str);
	if (src->len < 4 || src->len > 5)
        return (1);
	src->philos_nb = ft_atoi(p.str[0]);
	if (src->philos_nb <= 0 || src->time_to_die < 0
		|| src->time_to_eat < 0 || src->time_to_sleep < 0
		|| src->philos_nb > 10000)
		return (1);
	src->time_to_die = ft_atoi(p.str[1]);
	src->time_to_eat = ft_atoi(p.str[2]);
	src->time_to_sleep = ft_atoi(p.str[3]);
    if (src->len == 5)
	{
		src->times_philos_must_eat = ft_atoi(p.str[4]);
		if (src->times_philos_must_eat <= 0)
			return (1);
	}
	if (src->time_to_die <= 0 
		|| src->time_to_eat <= 0 || src->time_to_sleep <= 0)
		return (1);
	freedom(p.str);
    return (0);
}
