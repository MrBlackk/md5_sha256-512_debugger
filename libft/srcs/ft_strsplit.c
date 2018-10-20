/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 10:37:45 by vchornyi          #+#    #+#             */
/*   Updated: 2017/11/01 10:37:47 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int n;
	int is_word;

	n = 0;
	is_word = 0;
	while (*s)
	{
		if (*s == c)
			is_word = 0;
		else
		{
			if (is_word == 0)
				n++;
			is_word = 1;
		}
		s++;
	}
	return (n);
}

static void	skip_char(char const *s, char c, int *iter)
{
	while (s[*iter] && s[*iter] == c)
		(*iter)++;
}

static int	count_length(char const *s, char c)
{
	int len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static char	**get_words_array(char const *s, char c, int *n)
{
	char	**words;

	if (s == NULL)
		return (NULL);
	*n = count_words(s, c);
	words = (char **)malloc(sizeof(char *) * (*n + 1));
	if (words == NULL)
		return (NULL);
	return (words);
}

char		**ft_strsplit(char const *s, char c)
{
	int		n;
	int		i_word;
	char	**words;
	int		i;
	int		j;

	words = get_words_array(s, c, &n);
	if (words == NULL)
		return (NULL);
	i = 0;
	i_word = 0;
	while (i_word < n && s[i])
	{
		skip_char(s, c, &i);
		words[i_word] = ft_strnew(count_length(&s[i], c));
		if (words[i_word] == NULL)
			return (NULL);
		j = 0;
		while (s[i] && s[i] != c)
			words[i_word][j++] = s[i++];
		words[i_word++][j] = '\0';
	}
	words[i_word] = NULL;
	return (words);
}
