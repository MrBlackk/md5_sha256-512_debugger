/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:31:48 by vchornyi          #+#    #+#             */
/*   Updated: 2017/12/28 12:31:54 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length(ssize_t n)
{
	int			len;
	size_t		num;

	len = 0;
	num = n;
	if (n <= 0)
	{
		num = -n;
		len++;
	}
	while (num > 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char		*ft_ltoa(ssize_t n)
{
	int			len;
	size_t		num;
	char		*str;
	int			i;

	len = get_length(n);
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	i = 0;
	num = n;
	if (n < 0)
	{
		str[i++] = '-';
		num = -n;
	}
	str[len] = '\0';
	while (len > i)
	{
		str[len - 1] = num % 10 + '0';
		num = num / 10;
		len--;
	}
	return (str);
}
