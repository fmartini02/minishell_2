# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmartini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 16:18:30 by fmartini          #+#    #+#              #
#    Updated: 2024/04/09 16:18:30 by fmartini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
		ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
		ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_print_list.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c ft_utoa.c ft_uns_len.c  ft_num_len.c ft_print_mat_str.c \
		ft_putstr.c ft_putchar.c ft_strcmp.c ft_ispace.c \
		ft_ispace.c ft_matlen.c ft_word_len.c ft_skip_spaces.c \
		ft_strlen_till_space.c ft_strjoin_free.c free_mat.c\

OBJS	= $(SRCS:.c=.o)

NAME	= std_lib.a

CC	= cc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
	ar rc $(NAME) $(OBJS)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
