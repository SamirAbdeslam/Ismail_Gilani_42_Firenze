# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 19:13:20 by igilani           #+#    #+#              #
#    Updated: 2025/02/25 09:24:05 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Configurazioni principali
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g
NAME    = fractol
SRC     = main.c
OBJ_DIR = obj
OBJ     = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
LIB_DIR = tha_supreme_lib

# Colori ANSI
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RESET   = \033[0m

# Progress bar migliorata
define PROGRESS_BAR
    @printf "$(YELLOW)[$(RESET)$(BLUE)%-20s$(YELLOW)]$(RESET) %s\n" "$$(printf '=%.0s' {1..$$(( $1 * 20 / $(TOTAL) ))})" "$2"
endef

TOTAL := $(words $(SRC))
COUNT := 0

# Regole principali
all: $(NAME)
	@echo "$(GREEN)✔ Build completato$(RESET)"

$(NAME): $(OBJ) | libs
	@$(CC) $(CFLAGS) $^ -o $@ -L$(LIB_DIR) -l:tha_supreme_lib.a
	@echo "$(GREEN)✔ Eseguibile $(NAME) generato$(RESET)"

# Regola per compilare le librerie
libs:
	@$(MAKE) -s -C $(LIB_DIR)

# Regola per i file oggetto
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(eval COUNT = $(shell echo $$(($(COUNT)+1))))
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(call PROGRESS_BAR,$(COUNT),"Compiling $<")

$(OBJ_DIR):
	@mkdir -p $@

# Pulizia
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIB_DIR) clean
	@echo "$(RED)✔ Cartella $(OBJ_DIR) pulita$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIB_DIR) fclean
	@echo "$(RED)✔ Eseguibile $(NAME) rimosso$(RESET)"

re: fclean all

.PHONY: all clean fclean re libs