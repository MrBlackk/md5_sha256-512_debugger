/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 15:00:11 by vchornyi          #+#    #+#             */
/*   Updated: 2018/01/15 15:00:14 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*add_zeros_hex(char *hex_str, size_t num)
{
	size_t	len;
	char	*res;

	len = ft_strlen(hex_str);
	res = ft_strnew(len + num);
	if (!res)
		exit(1);
	ft_memset(res, '0', num);
	ft_strncpy(&res[num], hex_str, len);
	ft_strdel(&hex_str);
	return (res);
}

static void	add_alternative_hex(t_str *el, char **hex_str, size_t *arg_len)
{
	char *temp;

	if (el->fmt->is_sharp == 1
		&& (el->fmt->type == 'p' || *(int *)el->fmt->arg != 0))
	{
		temp = *hex_str;
		*hex_str = ft_strnew(*arg_len + 2);
		if (*hex_str == NULL)
			exit(1);
		(*hex_str)[0] = '0';
		(*hex_str)[1] = 'x';
		ft_strcpy(&(*hex_str)[2], temp);
		ft_strdel(&temp);
		*arg_len += 2;
	}
	if (el->fmt->type == 'X')
		ft_str_to_upper(*hex_str);
}

void		pf_format_hex(t_str *el)
{
	char	*hex_str;
	char	*res;
	size_t	arg_len;
	int		add;

	if ((hex_str = pf_get_unsigned_base(el, 16)) == NULL)
		exit(1);
	arg_len = ft_strlen(hex_str);
	if (!el->fmt->is_precision && !el->fmt->is_minus && el->fmt->is_zero)
	{
		add = (el->fmt->is_sharp == 1) ? 2 : 0;
		el->fmt->precision = (el->fmt->width > arg_len + add) ?
		el->fmt->width - add : 0;
	}
	if (arg_len < el->fmt->precision)
	{
		hex_str = add_zeros_hex(hex_str, el->fmt->precision - arg_len);
		arg_len = el->fmt->precision;
	}
	add_alternative_hex(el, &hex_str, &arg_len);
	if (el->fmt->precision == 0 && *(int *)el->fmt->arg == 0)
		arg_len = (el->fmt->type == 'p' ? 2 : 0);
	el->len = (arg_len < el->fmt->width) ? el->fmt->width : arg_len;
	res = pf_apply_width(el, hex_str, ' ', arg_len);
	pf_replace_format_str(el, res, hex_str);
}
