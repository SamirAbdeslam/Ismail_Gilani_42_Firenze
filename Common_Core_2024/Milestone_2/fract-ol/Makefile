# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 15:09:24 by igilani           #+#    #+#              #
#    Updated: 2025/03/03 15:09:25 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Comportamento predefinito
.DEFAULT_GOAL := silent

# Configurazioni principali
CC	  = cc
CFLAGS  = -Wall -Wextra -Werror -g -O3
NAME	= fractol
SRC	 = fractol.c render.c math_utils.c event_control.c
HEADERS = fractol.h
OBJ_DIR = obj
OBJ	 = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
LIB_DIR = tha_supreme_lib
MLX_DIR = minilibx-linux
BUILD = 0

# Librerie
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
THA_LIB = $(LIB_DIR)/tha_supreme_lib.a

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

$(MLX_LIB):
	@echo "$(BLUE)➜ Compilazione della libreria $(YELLOW)MinilibX$(RESET)$(BLUE)...$(RESET)"
	@if ! $(MAKE) -C $(MLX_DIR) > /dev/null 2>&1; then \
		echo "$(ERROR) Errore durante la compilazione di MinilibX$(RESET)"; \
		exit 1; \
	fi
	@echo "$(GREEN)✔ MinilibX compilata$(RESET)"

$(THA_LIB):
	@echo "$(BLUE)➜ Compilazione della libreria $(YELLOW)tha_supreme$(RESET)$(BLUE)...$(RESET)"
	@if ! $(MAKE) -C $(LIB_DIR) > /dev/null 2>&1; then \
		echo "$(ERROR) Errore durante la compilazione della libreria tha_supreme_lib$(RESET)"; \
		exit 1; \
	fi
	@echo "$(GREEN)✔ tha_supreme compilata$(RESET)"

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ || { \
		echo "$(ERROR) Errore nella compilazione di $<$(RESET)"; \
		exit 1; \
	}

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ) $(MLX_LIB) $(THA_LIB)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_LIB) -L$(LIB_DIR) -l:$(notdir $(THA_LIB)) -lm -lX11 -lXext || { \
		echo "$(ERROR) Errore durante il linking finale$(RESET)"; \
		exit 1; \
	}
	@$(eval BUILD = 1)
	@echo "$(BLUE)➜ Creazione eseguibile $(NAME)...$(RESET)"
	@echo "$(GREEN)✔ Eseguibile $(NAME) generato$(RESET)"

clean:
	@$(MAKE) -s -C $(LIB_DIR) clean > /dev/null 2>&1
	@echo "$(BLUE)➜ File oggetto da $(YELLOW)$(LIB_DIR)$(RESET) $(BLUE)rimossi$(RESET)"
	@$(MAKE) -s -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "$(BLUE)➜ File oggetto da $(YELLOW)$(MLX_DIR)$(RESET) $(BLUE)rimossi$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)➜ File oggetto $(YELLOW)$(NAME)$(RESET) $(BLUE)rimossi$(RESET)"

fclean: clean
	@$(MAKE) -s -C $(LIB_DIR) fclean > /dev/null 2>&1
	@$(MAKE) -s -C $(MLX_DIR) clean > /dev/null 2>&1
	@rm -f $(NAME)
	@echo "$(BLUE)➜ Eseguibile $(YELLOW)$(NAME)$(RESET) $(BLUE)rimosso$(RESET)"

re: fclean all

silent:
	@$(MAKE) all 2>&1 | grep -v '^make\[.*\]:'

.PHONY: all clean fclean re lib_check silent
