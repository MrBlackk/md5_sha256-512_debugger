/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:42:26 by vchornyi          #+#    #+#             */
/*   Updated: 2017/11/27 15:42:29 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		add_str(char **old, char *add, size_t size)
{
	size_t	len;
	char	*new;
	char	*n_char;

	n_char = ft_strchr(add, '\n');
	if (n_char != NULL)
		size = n_char - add;
	if (*old == NULL)
		if ((*old = ft_strnew(size)) == NULL)
			return (-1);
	len = ft_strlen(*old);
	new = ft_strnew(len + size);
	if (new == NULL)
		return (-1);
	ft_strncpy(new, *old, len);
	ft_strncpy(&new[len], add, size);
	free(*old);
	*old = new;
	return (n_char != NULL ? 1 : 0);
}

static t_tail	*add_new_tail(int file_desc, t_tail *prev)
{
	t_tail *new;

	new = (t_tail *)malloc(sizeof(t_tail));
	if (new == NULL)
		return (NULL);
	new->fd = file_desc;
	new->tail = NULL;
	new->size = 0;
	new->prev = prev;
	new->next = NULL;
	return (new);
}

static t_tail	*get_tail_by_fd(t_tail *tail, int file_desc)
{
	t_tail *new;

	if (tail == NULL)
	{
		if ((tail = add_new_tail(file_desc, NULL)) == NULL)
			return (NULL);
	}
	else
	{
		while (tail->prev)
			tail = tail->prev;
		if (tail->fd == file_desc)
			return (tail);
		while (tail->next)
		{
			tail = tail->next;
			if (tail->fd == file_desc)
				return (tail);
		}
		if ((new = add_new_tail(file_desc, tail)) == NULL)
			return (NULL);
		tail->next = new;
		tail = new;
	}
	return (tail);
}

static int		check_tail(t_tail *tail, char **line)
{
	size_t	n_len;
	char	*temp;

	temp = NULL;
	if ((ft_strchr(tail->tail, '\n')))
	{
		n_len = ft_strchr(tail->tail, '\n') - tail->tail;
		if ((*line = ft_strnew(n_len)) == NULL)
			return (-1);
		ft_strncpy(*line, tail->tail, n_len);
		tail->size = tail->size - n_len - 1;
		if (tail->size > 0)
			if ((temp = ft_strsub(tail->tail, n_len + 1, tail->size)) == NULL)
				return (-1);
		free(tail->tail);
		tail->tail = temp;
		return (1);
	}
	*line = ft_strnew(tail->size);
	if (*line == NULL)
		return (-1);
	ft_strncpy(*line, tail->tail, tail->size);
	free(tail->tail);
	tail->tail = NULL;
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	char			*r_buf;
	ssize_t			ret;
	int				is_n;
	static t_tail	*tail = NULL;

	tail = get_tail_by_fd(tail, fd);
	if (line == NULL || tail == NULL)
		return (-1);
	*line = NULL;
	if (tail->tail != NULL)
		if ((is_n = check_tail(tail, line)) == 1 || is_n == -1)
			return (is_n == 1 ? 1 : -1);
	if ((r_buf = ft_strnew(BUFF_SIZE)) == NULL)
		return (-1);
	is_n = 0;
	while (is_n == 0 && ((ret = read(fd, r_buf, BUFF_SIZE)) > 0))
		is_n = add_str(line, r_buf, (size_t)ret);
	if (ret < 0 || is_n == -1)
		return (ft_free_ret(r_buf, -1));
	if (is_n == 1
		&& (tail->size = ret - (ft_strchr(r_buf, '\n') - r_buf) - 1) > 0)
		if (!(tail->tail = ft_strsub(r_buf, ret - tail->size, tail->size)))
			return (-1);
	free(r_buf);
	return (*line == NULL ? 0 : 1);
}
