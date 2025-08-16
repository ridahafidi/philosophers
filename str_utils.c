/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhafidi <rhafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:49:43 by rhafidi           #+#    #+#             */
/*   Updated: 2025/08/16 22:51:06 by rhafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	char	*temp_nptr;
	int		sign;
	int		result;

	result = 0;
	sign = 1;
	temp_nptr = (char *)nptr;
	while (*temp_nptr == ' ' || (*temp_nptr >= 9 && *temp_nptr <= 13))
		temp_nptr++;
	if (*temp_nptr == '-')
	{
		sign = -1;
		temp_nptr++;
	}
	else if (*temp_nptr == '+')
		temp_nptr++;
	while (ft_isdigit(*temp_nptr))
	{
		result = (result * 10) + (*temp_nptr - '0');
		temp_nptr++;
	}
	return (result * sign);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
