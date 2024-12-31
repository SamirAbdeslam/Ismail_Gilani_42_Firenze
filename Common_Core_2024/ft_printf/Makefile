# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/28 13:40:36 by igilani           #+#    #+#              #
#    Updated: 2024/12/31 13:54:20 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Definisco il percorso del makefile di libft

LIBFT_PATH = libft
LIBFT_NAME = $(LIBFT_PATH)/libft.a

#Creo delle varibili per evitare di scrivere ogni volta i comandi

CC = cc
CFLAGS = -Wall -Wextra -Werror -c

#Definisco il nome della libreria
NAME = libftprintf.a

all: $(NAME)

#Passo i nomi dei file che deve compilare
SRCS = ft_printf.c

#Passo i nomi corrispondendi ai file da compilare con i file oggetti da creare
OBJS = $(SRCS:.c=.o)

#Creo il comando finale per compilare il tutto e le sue dependecies (OBJS)

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(OBJS2)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re libft