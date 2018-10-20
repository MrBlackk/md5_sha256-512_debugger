# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/25 15:00:12 by vchornyi          #+#    #+#              #
#    Updated: 2017/10/25 15:00:13 by vchornyi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror -I./includes
SRC_NAME = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
 ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstaddend.c\
 ft_lstat.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c\
 ft_lstnew.c ft_lstsize.c ft_memalloc.c ft_memccpy.c ft_memchr.c\
 ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c\
 ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c\
 ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_readfile.c ft_strcat.c\
 ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c\
 ft_strdup.c ft_strdupaddmem.c ft_strequ.c ft_striter.c ft_striteri.c\
 ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c\
 ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c\
 ft_strnstr.c ft_strrchr.c ft_strrev.c ft_strsplit.c ft_strstr.c\
 ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_lstdeldata.c\
 get_next_line.c ft_ltoa.c ft_ultoa_base.c\
 ft_printf.c ft_strbasetoul.c ft_putstr_len.c ft_wchar_to_str.c\
 ft_wstr_to_str.c ft_char_to_str.c ft_str_to_upper.c\
 pf_set_flags.c pf_format_to_t_str.c pf_format_digit.c pf_format_ch_str.c\
 pf_format_oct_uns.c pf_format_hex.c pf_format.c pf_format_bonus.c ft_free_ret.c
 
OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))
SRC_DIR = srcs/
OBJ_DIR = objs/

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "##### Lib created #####"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -o $@ -c $< $(INC)

clean:
	@rm -f $(OBJ)
	@echo "##### Removed lib object files #####"

fclean: clean
	@rm -f $(NAME)
	@echo "##### Removed libft.a #####"

re: fclean all

.PHONY: all clean fclean re