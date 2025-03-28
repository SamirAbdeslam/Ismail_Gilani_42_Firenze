# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 18:20:10 by igilani           #+#    #+#              #
#    Updated: 2025/03/28 18:20:59 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Configurazioni principali
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -O3 -Wno-unused-result
NAME		= push_swap
BONUS		= checker
SRC			= error_handle.c main.c push_command.c push_swap_command.c push_swap_init.c reverse_rotate_command.c rotate_command.c stack_init.c stack_utils.c swap_command.c tiny_sort.c idx.c rotate_both.c
SRC_BONUS	= bonus/checker_bonus.c error_handle.c push_command.c push_swap_command.c push_swap_init.c reverse_rotate_command.c rotate_command.c stack_init.c stack_utils.c swap_command.c tiny_sort.c idx.c rotate_both.c
HEADERS		= push_swap.h
OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_BONUS	= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_BONUS:.c=.o)))
LIB_DIR		= tha_supreme_lib
BUILD		= 0

# Librerie
THA_LIB = $(LIB_DIR)/tha_supreme_lib.a

# Colori ANSI
RED		= \033[31m
ERROR	= $(RED)✗
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m
RESET	= \033[0m

all: $(NAME)
	@if [ $(BUILD) -eq 1 ]; then \
		echo "$(GREEN)✔ Build completato$(RESET)"; \
	else \
		if [ $(BUILD) -eq 0 ]; then \
			echo "$(GREEN)✔ Già tutto compilato$(RESET)"; \
		fi \
	fi

bonus: $(BONUS)
	@if [ $(BUILD) -eq 1 ]; then \
		echo "$(GREEN)✔ Build completato per bonus$(RESET)"; \
	else \
		if [ $(BUILD) -eq 0 ]; then \
			echo "$(GREEN)✔ Già tutto compilato per bonus$(RESET)"; \
		fi \
	fi

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

$(OBJ_DIR)/%.o: bonus/%.c $(HEADERS) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ || { \
		echo "$(ERROR) Errore nella compilazione di $<$(RESET)"; \
		exit 1; \
	}

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ) $(THA_LIB)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(THA_LIB) || { \
		echo "$(ERROR) Errore durante il linking finale$(RESET)"; \
		exit 1; \
	}
	@$(eval BUILD = 1)
	@echo "$(BLUE)➜ Creazione eseguibile $(NAME)...$(RESET)"
	@echo "$(GREEN)✔ Eseguibile $(NAME) generato$(RESET)"

$(BONUS): $(OBJ_BONUS) $(THA_LIB)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(BONUS) $(THA_LIB) || { \
		echo "$(ERROR) Errore durante il linking finale per bonus$(RESET)"; \
		exit 1; \
	}
	@$(eval BUILD = 1)
	@echo "$(BLUE)➜ Creazione eseguibile $(BONUS)...$(RESET)"
	@echo "$(GREEN)✔ Eseguibile $(BONUS) generato$(RESET)"

clean:
	@$(MAKE) -s -C $(LIB_DIR) clean > /dev/null 2>&1
	@echo "$(BLUE)➜ File oggetto da $(YELLOW)$(LIB_DIR)$(RESET) $(BLUE)rimossi$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)➜ File oggetto $(YELLOW)$(NAME)$(RESET) $(BLUE)rimossi$(RESET)"

fclean: clean
	@$(MAKE) -s -C $(LIB_DIR) fclean > /dev/null 2>&1
	@rm -f $(NAME) $(BONUS)
	@echo "$(BLUE)➜ Eseguibili $(YELLOW)$(NAME) e $(BONUS)$(RESET) $(BLUE)rimossi$(RESET)"

re: fclean all

silent:
	@$(MAKE) all 2>&1 | grep -v '^make\[.*\]:'

.PHONY: all clean fclean re bonus silent