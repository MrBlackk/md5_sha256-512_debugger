/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 15:25:11 by vchornyi          #+#    #+#             */
/*   Updated: 2018/12/08 15:25:12 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			count_args(char *line)
{
	int	num;
	int	is_arg;
	int	is_q;

	num = 0;
	is_arg = 0;
	is_q = 0;
	while (*line)
	{
		if (ft_iswhitespace(*line) && !is_q)
			is_arg = 0;
		else if (*line == '"' && is_q)
			is_q = 0;
		else if (!is_q)
		{
			if (*line == '"')
				is_q = 1;
			if (is_arg == 0)
				num++;
			is_arg = 1;
		}
		line++;
	}
	return (num);
}

static unsigned int	count_length(char const *s)
{
	unsigned int	len;
	int				is_q;

	len = 0;
	is_q = 0;
	if (*s && *s == '"')
		is_q = 1;
	while (*s && (!ft_iswhitespace(*s) || is_q))
	{
		len++;
		s++;
		if (*s && *s == '"')
			is_q = 0;
	}
	return (len);
}

static char			**get_args_array(int argc)
{
	char	**words;

	words = (char **)malloc(sizeof(char *) * (argc + 1));
	if (words == NULL)
		return (NULL);
	words[0] = ft_strdup("ft_ssl");
	if (words[0] == NULL)
		return (NULL);
	words[argc] = NULL;
	return (words);
}

static char			*save_arg(char *line, int *i)
{
	int		j;
	char	*arg;
	int		is_q;

	if ((arg = ft_strnew(count_length(&line[*i]))) == NULL)
		return (NULL);
	j = 0;
	is_q = 0;
	if (line[*i] && line[*i] == '"')
		is_q = 1;
	while (line[*i] && (!ft_iswhitespace(line[*i]) || is_q))
	{
		if (line[*i] != '"')
			arg[j++] = line[(*i)++];
		else
			(*i)++;
		if (line[*i] && line[*i] == '"')
			is_q = 0;
	}
	arg[j] = '\0';
	return (arg);
}

char				**split_arg_line(char *line)
{
	int		i;
	int		i_arg;
	int		argc;
	char	**words;

	argc = count_args(line) + 1;
	if ((words = get_args_array(argc)) == NULL)
		return (NULL);
	i = 0;
	i_arg = 1;
	while (i_arg < argc && line[i])
	{
		while (line[i] && ft_iswhitespace(line[i]))
			i++;
		words[i_arg] = save_arg(line, &i);
		i_arg++;
		i++;
	}
	return (words);
}
