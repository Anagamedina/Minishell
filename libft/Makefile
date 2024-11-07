# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 18:38:08 by anamedin          #+#    #+#              #
#    Updated: 2024/11/07 14:18:34 by anamedin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
ARC = ar -rcs

NAME = libft.a
HEADER = libft.h

SRCS =  ft_bzero.c ft_calloc.c \
	ft_strjoin.c ft_strlen.c ft_substr.c \
	ft_strdup.c ft_strncmp.c ft_split.c \
	ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_putchar.c ft_putnbr.c ft_print_string.c ft_hex.c ft_unsignedint.c

SRC_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRC_BONUS:.c=.o)


#Regla implícita
all: $(NAME)

$(NAME): $(OBJS)
	$(ARC) $(NAME) $(OBJS)

bonus: $(OBJS) $(OBJS_BONUS)
		$(ARC) $(NAME) $(OBJS) $(OBJS_BONUS) 


%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all, clean, fclean, re all
