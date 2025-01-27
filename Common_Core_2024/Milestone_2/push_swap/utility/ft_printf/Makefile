# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 14:44:48 by igilani           #+#    #+#              #
#    Updated: 2025/01/27 17:11:16 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Definisco il percorso del makefile di libft
LIBFT_PATH = ../libft
LIBFT_NAME = $(LIBFT_PATH)/libft.a

# Creo delle variabili per evitare di scrivere ogni volta i comandi
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Definisco il nome della libreria
NAME = libftprintf.a

# Passo i nomi dei file che deve compilare
SRCS = ft_check/case_int.c ft_check/case_void.c ft_check/case_unsigned.c ft_check/case_char.c ft_printf.c

# Passo i nomi corrispondenti ai file da compilare con i file oggetti da creare
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_PATH)

# Creo il comando finale per compilare il tutto e le sue dipendenze (OBJS)
$(NAME): $(LIBFT_NAME) $(OBJS)
	cp $(LIBFT_PATH)/libft.a $(NAME)
	ar rcs $(NAME) $(LIBFT_NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(LIBFT_PATH)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re