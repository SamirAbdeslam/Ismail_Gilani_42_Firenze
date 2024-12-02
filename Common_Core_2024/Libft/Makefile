# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 18:06:52 by igilani           #+#    #+#              #
#    Updated: 2024/11/29 17:56:35 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Creo delle varibili per evitare di scrivere ogni volta i comandi

CC = cc
CFLAGS = -Wall -Wextra -Werror -c

#Definisco il nome della libreria
NAME = libft.a

all: $(NAME)

#Passo i nomi dei file che deve compilare
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_memchr.c ft_strncmp.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c

#Passo i nomi corrispondendi ai file da compilare con i file oggetti da creare
OBJS = $(SRCS:.c=.o)

#Creo il comando finale per compilare il tutto e le sue dependecies (OBJS)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
