/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupaddmem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 10:45:07 by vchornyi          #+#    #+#             */
/*   Updated: 2017/11/03 10:45:09 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdupaddmem(char *src, size_t *buf_size)
{
	size_t	len;
	char	*res;

	len = ft_strlen(src);
	*buf_size = len + len / 2;
	res = ft_strnew(*buf_size - 1);
	if (res == NULL)
	{
		free(src);
		return (NULL);
	}
	ft_memcpy(res, src, *buf_size);
	free(src);
	return (res);
}
