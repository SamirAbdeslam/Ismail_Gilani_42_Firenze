# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 17:04:02 by igilani           #+#    #+#              #
#    Updated: 2025/01/27 17:12:19 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Definisco il percorso del makefile di libft/ft_printf
UTILITY_PATH = utility/ft_printf
UTILITY_NAME = $(UTILITY_PATH)/libftprintf.a

# Creo delle variabili per evitare di scrivere ogni volta i comandi
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Definisco il nome della libreria
NAME = push_swap

# Passo i nomi dei file che deve compilare
SRCS = 

all: $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re