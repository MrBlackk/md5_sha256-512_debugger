/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_oct_uns.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 14:55:45 by vchornyi          #+#    #+#             */
/*   Updated: 2018/01/15 14:55:46 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*pf_get_unsigned_base(t_str *el, int base)
{
	if (el->fmt->length == 'H')
		return (ft_ultoa_base(*(unsigned char *)el->fmt->arg, base));
	else if (el->fmt->length == 'h')
		return (ft_ultoa_base(*(unsigned short int *)el->fmt->arg, base));
	else if (el->fmt->length == 'l')
		return (ft_ultoa_base(*(unsigned long int *)el->fmt->arg, base));
	else if (el->fmt->length == 'L')
		return (ft_ultoa_base(*(unsigned long long int *)el->fmt->arg, base));
	else if (el->fmt->length == 'j')
		return (ft_ultoa_base(*(uintmax_t *)el->fmt->arg, base));
	else if (el->fmt->length == 'z')
		return (ft_ultoa_base(*(size_t *)el->fmt->arg, base));
	return (ft_ultoa_base(*(unsigned int *)el->fmt->arg, base));
}

static char	*add_zeros_oct_uns(char *octal, size_t num)
{
	size_t	len;
	char	*res;

	len = ft_strlen(octal);
	res = ft_strnew(len + num);
	if (!res)
		exit(1);
	ft_memset(res, '0', num);
	ft_strncpy(&res[num], octal, len);
	ft_strdel(&octal);
	return (res);
}

void		pf_format_octal_binary(t_str *el, int base)
{
	char	fill_char;
	char	*octal_str;
	char	*res;
	size_t	arg_len;

	fill_char = ' ';
	if (el->fmt->is_zero == 1 && el->fmt->is_minus == 0)
		fill_char = '0';
	if ((octal_str = pf_get_unsigned_base(el, base)) == NULL)
		exit(1);
	arg_len = ft_strlen(octal_str);
	if (el->fmt->precision == 0 && *(int*)el->fmt->arg == 0)
		arg_len = 0;
	if (el->fmt->is_sharp && ((el->fmt->is_precision
		&& arg_len >= el->fmt->precision) || (octal_str[0] != '0'
		&& !el->fmt->is_precision)))
		el->fmt->precision = arg_len + 1;
	if (arg_len < el->fmt->precision)
	{
		octal_str = add_zeros_oct_uns(octal_str, el->fmt->precision - arg_len);
		arg_len = el->fmt->precision;
	}
	el->len = (arg_len < el->fmt->width) ? el->fmt->width : arg_len;
	res = pf_apply_width(el, octal_str, fill_char, arg_len);
	pf_replace_format_str(el, res, octal_str);
}

void		pf_format_unsigned(t_str *el)
{
	char	fill_char;
	char	*uns_str;
	char	*res;
	size_t	arg_len;

	fill_char = ' ';
	if (el->fmt->is_zero == 1 && el->fmt->is_minus == 0)
		fill_char = '0';
	uns_str = pf_get_unsigned_base(el, 10);
	if (!uns_str)
		exit(1);
	arg_len = ft_strlen(uns_str);
	if (el->fmt->precision == 0 && uns_str[0] == '0')
		arg_len = 0;
	if (arg_len < el->fmt->precision)
	{
		uns_str = add_zeros_oct_uns(uns_str, el->fmt->precision - arg_len);
		arg_len = el->fmt->precision;
	}
	el->len = (arg_len < el->fmt->width) ? el->fmt->width : arg_len;
	res = pf_apply_width(el, uns_str, fill_char, arg_len);
	pf_replace_format_str(el, res, uns_str);
}
