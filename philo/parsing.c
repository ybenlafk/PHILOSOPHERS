/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:13:15 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/05 17:36:37 by ybenlafk         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	fill_philos(t_src *src, t_philo **philos, t_var *vars, int stat)
{
	int	i;

	i = 0;
	while (i < src->philos_nb)
	{
		if (!i)
			*philos = new_philo(i + 1, src, vars, stat);
		else
			ft_lstadd_back(philos, new_philo(i + 1, src, vars, stat));
		i++;
	}
	ft_lstlast(*philos)->next = (*philos);
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
		return (freedom(p.str), 1);
	src->philos_nb = ft_atoi(p.str[0]);
	if (src->philos_nb <= 0 || src->philos_nb > 1000)
		return (freedom(p.str), 1);
	if (src_init(src, &p))
		return (freedom(p.str), 1);
	if (src->time_to_die <= 0
		|| src->time_to_eat <= 0 || src->time_to_sleep <= 0)
		return (freedom(p.str), 1);
	freedom(p.str);
	return (0);
}
