/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 15:15:40 by vchornyi          #+#    #+#             */
/*   Updated: 2017/12/29 15:15:41 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_length_for_base(size_t num, int base)
{
	size_t len;

	len = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num = num / base;
		len++;
	}
	return (len);
}

char			*ft_ultoa_base(size_t num, int base)
{
	char	*str;
	size_t	len;
	size_t	res;

	len = get_length_for_base(num, base);
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		res = num % base + '0';
		if (num % base > 9)
			res = num % base + 'a' - 10;
		str[len - 1] = (char)res;
		num = num / base;
		len--;
	}
	return (str);
}
