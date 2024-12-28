# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/28 13:40:36 by igilani           #+#    #+#              #
#    Updated: 2024/12/28 13:40:36 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Creo delle varibili per evitare di scrivere ogni volta i comandi

CC = cc
CFLAGS = -Wall -Wextra -Werror -c

#Definisco il nome della libreria
NAME = libftprintf.a

all: $(NAME)

#Passo i nomi dei file che deve compilare
LIBFT = libft/Makefile
SRCS = 

#Passo i nomi corrispondendi ai file da compilare con i file oggetti da creare
OBJS = $(SRCS:.c=.o)

#Creo il comando finale per compilare il tutto e le sue dependecies (OBJS)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(OBJS2)

fclean: clean
	rm -f $(NAME)

re: fclean all

libft: 
	$(LIBFT) make

.PHONY: all clean fclean re libft