/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:27:43 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/08 11:21:44 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo(int id, t_src *src, t_var *vars, int stat)
{
	pthread_mutex_t	fork;
	t_philo			*philo;

	pthread_mutex_init(&fork, NULL);
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->fork = fork;
	philo->src = src;
	philo->vars = vars;
	philo->ok = 1;
	philo->time_after_eat = get_time();
	if (stat)
	{
		philo->eat_count = 0;
		philo->eat_mode = 1;
	}
	philo->next = NULL;
	return (philo);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*p;

	if (lst && new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			p = ft_lstlast(*lst);
			p->next = new;
		}
	}
}

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
