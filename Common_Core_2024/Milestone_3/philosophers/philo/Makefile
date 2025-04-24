# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 14:47:16 by igilani           #+#    #+#              #
#    Updated: 2025/04/24 16:22:02 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Comportamento predefinito
.DEFAULT_GOAL := silent

# Configurazioni principali
CC	  	= cc
CFLAGS  = -Wall -Wextra -Werror -g -O3
NAME	= philo
SRC	 	= main.c error_handle.c parsing.c init.c dinner.c set_get.c print.c sync.c monitoring.c
HEADERS = philo.h
OBJ_DIR = obj
OBJ	 	= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
BUILD 	= 0

# Colori ANSI
RED	 = \033[31m
ERROR = $(RED)✗
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE	= \033[34m
RESET   = \033[0m

all: $(NAME)
	@if [ $(BUILD) -eq 1 ]; then \
		echo "$(GREEN)✔ Build completato$(RESET)"; \
	else \
		if [ $(BUILD) -eq 0 ]; then \
			echo "$(GREEN)✔ Già tutto compilato$(RESET)"; \
		fi \
	fi

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ || { \
		echo "$(ERROR) Errore nella compilazione di $<$(RESET)"; \
		exit 1; \
	}

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) || { \
		echo "$(ERROR) Errore durante il linking finale$(RESET)"; \
		exit 1; \
	}
	@$(eval BUILD = 1)
	@echo "$(BLUE)➜ Creazione eseguibile $(NAME)...$(RESET)"
	@echo "$(GREEN)✔ Eseguibile $(NAME) generato$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)➜ File oggetto $(YELLOW)$(NAME)$(RESET) $(BLUE)rimossi$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)➜ Eseguibile $(YELLOW)$(NAME)$(RESET) $(BLUE)rimosso$(RESET)"

re: fclean all

silent:
	@$(MAKE) all 2>&1 | grep -v '^make\[.*\]:'

.PHONY: all clean fclean re lib_check silent
