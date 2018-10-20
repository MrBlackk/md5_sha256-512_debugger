/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:00:35 by vchornyi          #+#    #+#             */
/*   Updated: 2017/10/29 15:00:36 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_result(long long res, int is_ok, int sign)
{
	if (is_ok == 0)
	{
		if (sign == -1)
			return (0);
		return (-1);
	}
	return (res * sign);
}

int			ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	long long	res;
	int			is_ok;

	is_ok = 1;
	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) && is_ok == 1)
	{
		if (res * 10 + str[i] - '0' < res)
			is_ok = 0;
		res = res * 10 + str[i++] - '0';
	}
	return (get_result(res, is_ok, sign));
}
