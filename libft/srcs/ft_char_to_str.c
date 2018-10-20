/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:06:36 by vchornyi          #+#    #+#             */
/*   Updated: 2018/01/12 18:06:37 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_char_to_str(unsigned char c)
{
	char *res;

	res = ft_strnew(1);
	if (!res)
		return (NULL);
	res[0] = c;
	return (res);
}
