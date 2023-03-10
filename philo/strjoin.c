/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:36:42 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/02/26 21:50:05 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ftstrlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!dest || !src)
		return (dest);
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*get_str(int size, char **strs, char *sep)
{
	char	*str;
	int		i;
	int		sep_l;
	int		str_l;

	str_l = 0;
	i = 0;
	if (size == 0)
	{
		str = malloc(sizeof(char));
		*str = 0;
		return (str);
	}
	while (i < size)
	{
		str_l += ftstrlen(strs[i]);
		i++;
	}
	sep_l = ftstrlen(sep) * (size - 1);
	str = malloc(sizeof(char) * (str_l + sep_l) + 1);
	return (str);
}

int	checkdb(int size, char **str)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] >= '0' && str[i][j] <= '9')
				break ;
			j++;
		}
		if (j == ftstrlen(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		j;
	int		k;
	int		i;
	char	*str;

	if (checkdb(size, strs) == 0)
		return (NULL);
	str = get_str(size, strs, sep);
	i = -1;
	k = 0;
	while (++i < size)
	{
		j = 0;
		while (strs[i][j])
			str[k++] = strs[i][j++];
		j = 0;
		while (sep[j] && i != size - 1)
			str[k++] = sep[j++];
	}
	str[k] = '\0';
	return (str);
}
