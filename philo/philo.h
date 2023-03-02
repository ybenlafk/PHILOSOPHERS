/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:58:46 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/03/02 14:05:21 by ybenlafk         ###   ########.fr       */
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
	int				philos_nb;
	int				len;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		times_philos_must_eat;
}					t_src;

typedef struct var
{
	char			*s;
	char			**str;
	int				i;
	int				rep;
	int				is;
	int				len;
	int				idd;
	long long		time;
	long long		time_after_eat;
	pthread_t		threads;
	pthread_mutex_t	lock;
	pthread_mutex_t	ls;
	pthread_mutex_t	lss;
}					t_var;

typedef struct s_philo
{
	int				id;
	long long		time_after_eat;
	int				ok;
	int				eat_count;
	int				eat_mode;
	pthread_mutex_t	fork;
	t_src			*src;
	t_var			*vars;
	struct s_philo	*next;
}					t_philo;

long long	ft_atoi(char *str);
long long	get_time(void);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(int size, char **strs, char *sep);
void		freedom(char **p);
void		fill_philos(t_src *src, t_philo **philos, t_var *vars, int stat);
void		*routine(void *param);
int			parsing(int ac, char **av, t_src *src);
int			src_init(t_src *src, t_var *p);
void		ft_usleep(long long time);
t_philo		*new_philo(int id, t_src *src, t_var *vars, int stat);
t_philo		*ft_lstlast(t_philo *lst);
void		ft_lstadd_back(t_philo **lst, t_philo *new);
void		created_philos(t_philo *philo, t_src *src, t_var *vars);
void		list_free(t_philo **philos, int len);
void		eat_counter(t_philo *philos);

#endif
