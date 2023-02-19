/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:58:46 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/02/19 16:17:27 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct src
{
    int         philos_nb;
    long long   time_to_die;
    long long   time_to_eat;
    long long   time_to_sleep;
    long long   times_philos_must_eat;
    long long   time;
    pthread_mutex_t forks[10000];
    pthread_t threads[10000];
}               t_src;

typedef struct var
{
    // philo       *tmp;
	char		*s;
	char		**str;
	int			i;
	int			j;
	int			len;
    long long time;
}	t_var;

typedef struct s_philo
{
    int         id;
    int         die;
    pthread_mutex_t *fork_one;
    pthread_mutex_t *fork_two;
    t_src           *src;
    t_var           *vars;
    pthread_t   *pth; 
}               philo;


long long	ft_atoi(char *str);
long long	get_time();
char	*ft_strjoin(int size, char **strs, char *sep);
char	**ft_split(char const	*s, char c);
void	freedom(char **p);
void	fill_philos(t_src *src, philo *philos, t_var *vars);
void    *routine(void *param);
int	parsing(int ac, char **av, t_src *src);

#endif