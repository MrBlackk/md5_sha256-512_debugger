/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbasetoul.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 13:16:50 by vchornyi          #+#    #+#             */
/*   Updated: 2018/01/12 13:16:52 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strbasetoul(char *str, int base)
{
	size_t	res;
	int		c;

	res = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		c = *str;
		if (ft_isdigit(c))
			c = *str - '0';
		else if (ft_isalpha(c))
			c = ft_tolower(c) - 'a' + 10;
		res = res * base + c;
		str++;
	}
	return (res);
}
