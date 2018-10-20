/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_ch_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 14:34:44 by vchornyi          #+#    #+#             */
/*   Updated: 2018/01/15 14:34:45 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pf_replace_format_str(t_str *el, char *str, char *arg_str)
{
	ft_strdel(&arg_str);
	ft_strdel(&el->str);
	el->str = str;
	if (el->fmt->arg && el->fmt->type != 's'
		&& el->fmt->type != 'S' && el->fmt->type != 'n'
		&& el->fmt->type != 'r' && el->fmt->type != 't')
		ft_memdel(&el->fmt->arg);
	ft_memdel((void **)&el->fmt);
}

char	*pf_apply_width(t_str *el, char *arg_str, char fill, size_t arg_width)
{
	char *res;

	res = ft_strnew(el->len);
	if (!res)
		exit(1);
	if (el->fmt->is_minus == 1)
	{
		ft_memcpy(res, arg_str, arg_width);
		ft_memset(&res[arg_width], fill, el->len - arg_width);
	}
	else
	{
		ft_memset(res, fill, el->len - arg_width);
		ft_memcpy(&res[el->len - arg_width], arg_str, arg_width);
	}
	return (res);
}

void	pf_format_char(t_str *el)
{
	char	*res;
	char	fill_char;
	char	*chr;
	size_t	chr_width;

	fill_char = ' ';
	if (el->fmt->is_zero == 1 && el->fmt->is_minus != 1)
		fill_char = '0';
	if (el->fmt->length == 'l' || el->fmt->type == 'C')
		chr = ft_wchar_to_str(*(wchar_t *)el->fmt->arg);
	else
		chr = ft_char_to_str(*(unsigned char *)el->fmt->arg);
	if (chr == NULL)
		exit(1);
	chr_width = ft_strlen(chr);
	if (chr_width == 0 && el->fmt->is_ok)
		chr_width = 1;
	if (el->fmt->width == 0)
		el->fmt->width = chr_width;
	el->len = el->fmt->width;
	res = pf_apply_width(el, chr, fill_char, chr_width);
	pf_replace_format_str(el, res, chr);
}

void	pf_format_string(t_str *el)
{
	char	fill_char;
	char	*res;
	size_t	arg_len;
	char	*arg;

	fill_char = ' ';
	if (el->fmt->is_zero == 1 && el->fmt->is_minus == 0)
		fill_char = '0';
	arg = NULL;
	if (el->fmt->arg == NULL)
		arg = ft_strdup("(null)");
	else if (el->fmt->length == 'l' || el->fmt->type == 'S')
		arg = ft_wstr_to_str((wchar_t *)el->fmt->arg, el);
	else if ((char *)el->fmt->arg != NULL)
		arg = ft_strdup((char *)el->fmt->arg);
	if (arg == NULL)
		exit(1);
	arg_len = ft_strlen(arg);
	if (el->fmt->is_precision && el->fmt->precision < arg_len)
		arg_len = el->fmt->precision;
	if (el->fmt->is_precision && el->fmt->precision == 0)
		arg_len = 0;
	el->len = (arg_len < el->fmt->width) ? el->fmt->width : arg_len;
	res = pf_apply_width(el, arg, fill_char, arg_len);
	pf_replace_format_str(el, res, arg);
}
