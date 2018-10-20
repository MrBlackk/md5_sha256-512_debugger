/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:00:52 by vchornyi          #+#    #+#             */
/*   Updated: 2017/10/25 15:00:53 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

# define BUFF_SIZE 10

typedef struct s_format	t_format;
typedef struct s_str	t_str;
typedef struct s_list	t_list;
typedef struct s_tail	t_tail;

struct	s_list
{
	void	*content;
	size_t	content_size;
	t_list	*next;
};

struct	s_tail
{
	int		fd;
	char	*tail;
	size_t	size;
	t_tail	*prev;
	t_tail	*next;
};

va_list	g_args;
int		g_len;

struct	s_format
{
	void	*arg;
	size_t	width;
	size_t	precision;
	char	length;
	char	type;
	int		is_ok;
	int		is_precision;
	int		is_wild;
	int		is_space;
	int		is_minus;
	int		is_plus;
	int		is_sharp;
	int		is_zero;
};

struct	s_str
{
	char		*str;
	size_t		len;
	t_format	*fmt;
	t_str		*next;
};

void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strnstr(const char *haystack,
		const char *needle, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s);
char	**ft_strsplit(char const *s, char c);
char	*ft_itoa(int n);
void	ft_putchar(char c);
void	ft_putstr(char const *s);
void	ft_putendl(char const *s);
void	ft_putnbr(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void const *content, size_t content_size);
void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void	ft_lstadd(t_list **alst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void	ft_lstaddend(t_list **alst, t_list *new);
t_list	*ft_lstat(t_list *lst, size_t el_at);
size_t	ft_lstsize(t_list *lst);
char	*ft_readfile(int file_desc, size_t buf_size);
char	*ft_strdupaddmem(char *src, size_t *buf_size);
char	*ft_strrev(char *str);
void	ft_lstdeldata(void *content, size_t content_size);
int		get_next_line(const int fd, char **line);
int		ft_free_ret(char *str, int ret);
char	*ft_ltoa(ssize_t n);
char	*ft_ultoa_base(size_t num, int base);
int		ft_printf(const char *format, ...);
size_t	ft_strbasetoul(char *str, int base);
void	ft_putstr_len(char *str, size_t len);
char	*ft_wchar_to_str(wchar_t wide);
char	*ft_wstr_to_str(wchar_t *wide, t_str *el);
char	*ft_char_to_str(unsigned char c);
void	ft_str_to_upper(char *str);
t_str	*pf_get_t_str(const char *format);
void	pf_set_flags(t_str *head);
void	pf_format_digit(t_str *el);
char	*pf_apply_width(t_str *el, char *arg_str, char fill, size_t arg_width);
void	pf_replace_format_str(t_str *el, char *str, char *arg_str);
void	pf_format_char(t_str *el);
void	pf_format_string(t_str *el);
char	*pf_get_unsigned_base(t_str *el, int base);
void	pf_format_octal_binary(t_str *el, int base);
void	pf_format_unsigned(t_str *el);
void	pf_format_hex(t_str *el);
void	pf_format_elements(t_str **head);
void	pf_format_non_printable(t_str *el);
void	pf_format_caesar(t_str *el);

#endif
