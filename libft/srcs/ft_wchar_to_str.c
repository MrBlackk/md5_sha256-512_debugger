/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 14:04:40 by vchornyi          #+#    #+#             */
/*   Updated: 2018/01/12 14:04:42 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	add_bits_to_mask(char *mask, char *bits)
{
	int j;
	int k;

	j = (int)ft_strlen(bits) - 1;
	k = (int)ft_strlen(mask) - 1;
	while (j >= 0 && k >= 0)
	{
		while (k >= 0 && mask[k] != 'x')
			k--;
		if (mask[k] == 'x')
			mask[k] = bits[j];
		j--;
		k--;
	}
	while (*mask)
	{
		if (*mask == 'x')
			*mask = '0';
		mask++;
	}
	ft_strdel(&bits);
}

static char	*bits_to_str(char *bits)
{
	char	*oct;
	int		bit_len;
	char	*res;
	size_t	num;
	int		i;

	bit_len = (int)ft_strlen(bits);
	res = ft_strnew((size_t)bit_len / 8);
	if (res == NULL)
		return (NULL);
	i = 0;
	while ((i + 1) * 8 <= bit_len)
	{
		oct = ft_strsub(bits, i * 8, 8);
		if (oct == NULL)
			return (NULL);
		num = ft_strbasetoul(oct, 2);
		ft_strdel(&oct);
		res[i] = num;
		i++;
	}
	ft_strdel(&bits);
	return (res);
}

char		*ft_wchar_to_str(wchar_t wide)
{
	int		bit_len;
	char	*bits;
	char	*mask;

	bits = ft_ultoa_base((size_t)wide, 2);
	if (bits == NULL)
		return (NULL);
	bit_len = (int)ft_strlen(bits);
	if (bit_len <= 7)
		mask = ft_strdup("0xxxxxxx");
	else if (bit_len <= 11)
		mask = ft_strdup("110xxxxx10xxxxxx");
	else if (bit_len <= 16)
		mask = ft_strdup("1110xxxx10xxxxxx10xxxxxx");
	else if (bit_len <= 21)
		mask = ft_strdup("11110xxx10xxxxxx10xxxxxx10xxxxxx");
	else
		mask = ft_strdup("0xxxxxxx");
	if (mask == NULL)
		return (NULL);
	add_bits_to_mask(mask, bits);
	return (bits_to_str(mask));
}
