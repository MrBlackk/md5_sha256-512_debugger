/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 10:40:31 by vchornyi          #+#    #+#             */
/*   Updated: 2017/11/03 10:40:33 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_readfile(int file_desc, size_t buf_size)
{
	char	read_buf[1];
	size_t	len;
	int		ret;
	char	*str;

	len = 0;
	str = ft_strnew(buf_size);
	if (str == NULL)
		return (NULL);
	while ((ret = read(file_desc, read_buf, 1)))
	{
		if (len == buf_size)
		{
			str = ft_strdupaddmem(str, &buf_size);
			if (str == NULL)
				return (NULL);
		}
		str[len] = read_buf[0];
		len++;
	}
	if (ret < 0)
		return (NULL);
	str[len] = '\0';
	return (str);
}
