# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdalloli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 15:59:05 by mdalloli          #+#    #+#              #
#    Updated: 2024/06/02 18:23:38 by abonanno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c functions.c num_control.c get.c get_numbers.c
OBJ = $(SRC:.c=.o)
TARGET = rush-02

# target di default
all: $(TARGET)

# regola per costruire l'eseguibile
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# regole per costruire i file oggetto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# pulizia dei file oggetto
clean:
	rm -f $(OBJ)

# pulizia completa (file oggetto ed eseguibile)
fclean: clean
	rm -f $(TARGET)

# ricostruzione completa
re: fclean all