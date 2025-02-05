# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 15:15:41 by igilani           #+#    #+#              #
#    Updated: 2025/02/05 13:13:40 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Barra di avanzamento
define PROGRESS_BAR 
	@echo -n "$(YELLOW)[$(RESET)$(BLUE)"; \
	for i in `seq 1 19`; do \
		echo -n "="; \
		sleep 0.03; \
	done; \
	echo -n "$(YELLOW)]$(RESET)"; \
	echo "$(1) $(2)$(RESET)"
endef

define PROGRESS_BAR_START
    @echo -n "$(YELLOW)[$(RESET)$(BLUE)"
endef

define PROGRESS_BAR_UPDATE
    @echo -n "="
endef

define PROGRESS_BAR_END
    @echo -n "$(YELLOW)]$(RESET)"; \
    echo "$(1) $(2)$(RESET)"
endef

# Configurazioni
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
DEBUG   = -g
NAME    = pipex
SRC     = pipex.c utils.c
OBJ_DIR = obj
OBJ     = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
LIB     = tha_supreme_lib/tha_supreme_lib.a
RICOMP  = $(YELLOW)[$(RESET)$(BLUE)=====$(RESET)$(GREEN)RICOMPILO$(RESET)$(BLUE)=====$(RESET)$(YELLOW)]$(RESET)

# Colori
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RESET   = \033[0m

# Regole principali
all: $(NAME)
	$(call PROGRESS_BAR_END,\033[32m,Eseguibile \033[33mpipex\033[0m \033[32mgenerato)

# Crea cartella obj e compila libreria
$(OBJ_DIR):
	@mkdir -p $@
	$(call PROGRESS_BAR_START)

$(LIB):
	@$(MAKE) -s -C tha_supreme_lib

# Compilazione progetto principale
$(NAME): $(OBJ) $(LIB)
	@$(CC) $(CFLAGS) $^ -o $@
	$(call PROGRESS_BAR_UPDATE)

# Regola per i file oggetto
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call PROGRESS_BAR_UPDATE)

# Pulizia
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C tha_supreme_lib clean
	$(call PROGRESS_BAR,\033[31m,Cartella $(OBJ_DIR) pulita!)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C tha_supreme_lib fclean
	$(call PROGRESS_BAR,\033[31m,Eseguibile rimosso!)

re: fclean
	@echo "$(RICOMP)"
	@$(MAKE) --no-print-directory all

.PHONY: all clean fclean re