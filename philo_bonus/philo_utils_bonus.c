/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:11:44 by jdoh              #+#    #+#             */
/*   Updated: 2023/04/08 10:11:45 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	idx;

	idx = 0;
	while (*(str++))
		++idx;
	return (idx);
}

t_milisec	time_interval(struct timeval *start_time, struct timeval *cur_time)
{
	return ((cur_time->tv_sec - start_time->tv_sec) * 1000
		+ (cur_time->tv_usec - start_time->tv_usec) / 1000);
}

int	philo_atoi(const char *str)
{
	long long	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		++str;
	if (*str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *(str++) - '0';
		if (result > 2147483647)
			return (RET_FAILURE);
	}
	if (*str != '\0' || result == 0)
		return (RET_FAILURE);
	return (result);
}

char	*small_itoa(int num)
{
	char	*result;
	int		order;
	int		tmp;
	int		idx;

	order = 0;
	tmp = num;
	while (tmp)
	{
		++order;
		tmp /= 10;
	}
	result = (char *) malloc(sizeof(char) * (order + 1));
	if (result == NULL)
		return (NULL);
	idx = order - 1;
	while (num)
	{
		result[idx--] = num % 10;
		num /= 10;
	}
	result[order] = '\0';
	return (result);
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*joined_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	idx;

	if (s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined_str = (char *) malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (joined_str == NULL)
	{
		free(s2);
		return (NULL);
	}
	idx = -1;
	while (++idx < s1_len)
		joined_str[idx] = s1[idx];
	idx = -1;
	while (++idx < s2_len)
		joined_str[idx + s1_len] = s2[idx];
	joined_str[s1_len + s2_len] = '\0';
	free(s2);
	return (joined_str);
}
