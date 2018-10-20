/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:48:17 by vchornyi          #+#    #+#             */
/*   Updated: 2017/12/15 13:48:19 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	apply_width_precision(t_str *el, size_t wild_i, int val, char *wild)
{
	if (el->str[wild_i - 1] == '.')
	{
		if (val >= 0)
			el->fmt->precision = (size_t)val;
		else
		{
			el->fmt->is_precision = 0;
			el->fmt->precision = 1;
		}
	}
	else
	{
		while (*wild)
		{
			if (ft_isdigit(*wild) && *(wild - 1) != '.')
				return ;
			wild++;
		}
		el->fmt->width = (size_t)val;
	}
}

static void	apply_wilds(t_str *el)
{
	int		val;
	size_t	wild_i;
	char	*wild;

	while ((wild = ft_strchr(el->str, '*')))
	{
		val = va_arg(g_args, int);
		wild_i = wild - el->str;
		if (val < 0 && el->fmt->type == 's')
			val = -val;
		else if (val < 0 && el->str[wild_i - 1] != '.')
		{
			el->fmt->is_minus = 1;
			val = -val;
		}
		apply_width_precision(el, wild_i, val, wild);
		el->str[wild_i] = '!';
	}
}

static void	get_additional_args(t_str *iter, char tp)
{
	size_t	*u_num;

	if (tp == 'o' || tp == 'O' || tp == 'x' || tp == 'X'
	|| tp == 'u' || tp == 'U' || tp == 'p' || tp == 'b')
	{
		if ((u_num = (size_t *)malloc(sizeof(size_t))) == NULL)
			exit(1);
		*u_num = va_arg(g_args, size_t);
		iter->fmt->arg = u_num;
	}
	else if (tp == 'n')
		iter->fmt->arg = va_arg(g_args, size_t*);
}

static void	get_args(t_str *iter, char tp)
{
	ssize_t	*s_num;

	if (iter->fmt->is_wild)
		apply_wilds(iter);
	if (tp == 'i' || tp == 'd' || tp == 'D' || tp == 'c' || tp == 'C')
	{
		if ((s_num = (ssize_t *)malloc(sizeof(ssize_t))) == NULL)
			exit(1);
		*s_num = va_arg(g_args, ssize_t);
		iter->fmt->arg = s_num;
	}
	else if (tp == 'S' || (tp == 's' && iter->fmt->length == 'l'))
		iter->fmt->arg = va_arg(g_args, wchar_t*);
	else if (tp == 's' || tp == 'r' || tp == 't')
		iter->fmt->arg = va_arg(g_args, char*);
	get_additional_args(iter, tp);
}

int			ft_printf(const char *format, ...)
{
	t_str *head;
	t_str *iter;

	g_len = 0;
	head = pf_get_t_str(format);
	iter = head;
	va_start(g_args, format);
	while (iter)
	{
		pf_set_flags(iter);
		if (iter->fmt && iter->fmt->is_ok)
			get_args(iter, iter->fmt->type);
		iter = iter->next;
	}
	va_end(g_args);
	pf_format_elements(&head);
	return (g_len);
}
