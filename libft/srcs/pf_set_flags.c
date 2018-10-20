/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_set_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 13:29:47 by vchornyi          #+#    #+#             */
/*   Updated: 2018/01/12 13:29:48 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_flag(t_str *el)
{
	char	*p;

	p = el->str;
	el->fmt->is_sharp = 0;
	el->fmt->is_minus = 0;
	el->fmt->is_plus = 0;
	el->fmt->is_space = 0;
	el->fmt->is_zero = 0;
	while (*p)
	{
		if (*p == '#')
			el->fmt->is_sharp = 1;
		if (*p == '-')
			el->fmt->is_minus = 1;
		if (*p == '+')
			el->fmt->is_plus = 1;
		if (*p == ' ')
			el->fmt->is_space = 1;
		if (*p == '0' && !ft_isdigit(*(p - 1)) && *(p - 1) != '.')
			el->fmt->is_zero = 1;
		p++;
	}
}

static void	set_length(t_str *el)
{
	el->fmt->length = '\0';
	if (ft_strstr(el->str, "z"))
		el->fmt->length = 'z';
	else if (ft_strstr(el->str, "j"))
		el->fmt->length = 'j';
	else if (ft_strstr(el->str, "ll"))
		el->fmt->length = 'L';
	else if (ft_strstr(el->str, "l"))
		el->fmt->length = 'l';
	else if (ft_strstr(el->str, "hh"))
		el->fmt->length = 'H';
	else if (ft_strstr(el->str, "h"))
		el->fmt->length = 'h';
}

static void	set_width(t_str *el)
{
	char	*p;
	int		is_get;

	is_get = 0;
	el->fmt->width = 0;
	p = el->str;
	while (*p)
	{
		if ((*p >= '1' && *p <= '9') && *(p - 1) != '.'
			&& !(*(p - 1) >= '1' && *(p - 1) <= '9') && is_get == 0)
		{
			el->fmt->width = (size_t)ft_atoi(p);
			is_get = 1;
		}
		if (!ft_isdigit(*p))
			is_get = 0;
		p++;
	}
}

static void	set_precision(t_str *el)
{
	char	*p;
	int		is_get;

	is_get = 0;
	p = el->str;
	el->fmt->precision = 1;
	el->fmt->is_precision = 0;
	if (ft_strchr(el->str, '.'))
		el->fmt->is_precision = 1;
	while (*p)
	{
		if (*p == '.')
			el->fmt->precision = 0;
		if (ft_isdigit(*p) && *(p - 1) == '.' && is_get == 0)
		{
			el->fmt->precision = (size_t)ft_atoi(p);
			is_get = 1;
		}
		if (!ft_isdigit(*p))
			is_get = 0;
		p++;
	}
}

void		pf_set_flags(t_str *head)
{
	if (head->fmt)
	{
		set_flag(head);
		set_length(head);
		set_width(head);
		set_precision(head);
	}
}
