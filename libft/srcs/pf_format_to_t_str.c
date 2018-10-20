/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_to_t_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:22:36 by vchornyi          #+#    #+#             */
/*   Updated: 2018/01/12 15:22:37 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_str	*create_new_str(size_t len, char *str, int is_format)
{
	t_str	*el;
	char	*s_num;

	if ((el = (t_str *)malloc(sizeof(t_str))) == NULL)
		exit(1);
	el->len = len;
	el->str = str;
	el->fmt = NULL;
	if (is_format == 0)
		return (el);
	if ((el->fmt = (t_format *)malloc(sizeof(t_format))) == NULL)
		exit(1);
	el->fmt->is_ok = 1;
	if (is_format == 1)
		el->fmt->type = el->str[len];
	else if (is_format == 2)
	{
		el->fmt->is_ok = 0;
		el->fmt->type = 'c';
		if ((s_num = (char *)malloc(sizeof(char))) == NULL)
			exit(1);
		*s_num = el->str[len];
		el->fmt->arg = s_num;
	}
	return (el);
}

static void		add_new_t_str(t_str **head, size_t len, char *str, int is_fmt)
{
	t_str *iter;
	t_str *el;

	el = create_new_str(len, str, is_fmt);
	el->next = NULL;
	if (el->fmt)
	{
		el->fmt->is_wild = 0;
		if (ft_strchr(el->str, '*'))
			el->fmt->is_wild = 1;
	}
	if (head && *head)
	{
		iter = *head;
		while (iter->next)
			iter = iter->next;
		iter->next = el;
	}
	else if (head && !*head)
		*head = el;
}

static void		add_format_to_t_str(const char **format, t_str **head)
{
	char	*converters;
	char	*flags;
	size_t	len;
	char	*str;

	converters = "sSpdDioOuUxXcCnrbt";
	flags = ".123456789#0-+ hljz*";
	len = 1;
	while (**format && ft_strchr(flags, **format) != NULL)
	{
		(*format)++;
		len++;
	}
	str = ft_strnew(len + 1);
	if (!str)
		exit(1);
	ft_strncpy(str, *format - len, len + 1);
	if (**format && ft_strchr(converters, **format) != NULL)
		add_new_t_str(head, len, str, 1);
	else
		add_new_t_str(head, len, str, 2);
	if (**format)
		(*format)++;
}

static void		add_str_to_t_str(const char **format, t_str **head)
{
	char	*str;
	size_t	len;

	len = 0;
	while (**format && **format != '%')
	{
		len++;
		(*format)++;
	}
	str = ft_strnew(len);
	if (!str)
		exit(1);
	ft_strncpy(str, *format - len, len);
	add_new_t_str(head, len, str, 0);
}

t_str			*pf_get_t_str(const char *format)
{
	t_str	*head;

	head = NULL;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			add_format_to_t_str(&format, &head);
		}
		else
			add_str_to_t_str(&format, &head);
	}
	return (head);
}
