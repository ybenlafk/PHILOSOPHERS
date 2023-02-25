/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:58:46 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/02/25 19:00:12 by ybenlafk         ###   ########.fr       */
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
    int         len;
    long long   time_to_die;
    long long   time_to_eat;
    long long   time_to_sleep;
    long long   times_philos_must_eat;
    pthread_mutex_t forks[100000];
    pthread_t threads[100000];
}               t_src;

typedef struct var
{
	char		*s;
	char		**str;
	int			i;
	int			j[1000];
	int			is;
	int			len;
    int         idd;
    long long time;
    long long time_after_eat;
    pthread_mutex_t lock;
    pthread_mutex_t ls;
}	t_var;

typedef struct s_philo
{
    int         id;
    int         j;
    int         rep;
    long long   time_after_eat;
    int         eat_count;
    int         eat_mode;
    pthread_mutex_t *fork_one;
    pthread_mutex_t *fork_two;
    t_src           *src;
    t_var           *vars;
    pthread_t       thd;
}               philo;


long long	ft_atoi(char *str);
long long	get_time();
char	**ft_split(char const	*s, char c);
char	*ft_strjoin(int size, char **strs, char *sep);
void	freedom(char **p);
void	fill_philos(t_src *src, philo *philos, t_var *vars, int stat);
void    *routine(void *param);
int	parsing(int ac, char **av, t_src *src);
int	is_death(philo *philos, t_src *src);

#endif