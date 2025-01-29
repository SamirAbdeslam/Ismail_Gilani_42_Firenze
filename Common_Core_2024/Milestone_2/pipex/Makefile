# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 10:59:20 by igilani           #+#    #+#              #
#    Updated: 2025/01/29 12:29:40 by igilani          ###   ########.fr        #
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

# Esempio di Makefile con colori
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
NAME    = pipex
SRC     = main.c
OBJ_DIR = obj
OBJ     = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
RICOMP  = $(YELLOW)[$(RESET)$(BLUE)=====$(RESET)$(GREEN)RICOMPILO$(RESET)$(BLUE)=====$(RESET)$(YELLOW)]$(RESET)

# Definizione dei colori
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RESET   = \033[0m

# Regole principali
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@
	$(call PROGRESS_BAR,\033[32m,Eseguibile $@ generato)

# Regola per i file oggetto
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call PROGRESS_BAR,\033[34m,Creata cartella $(OBJ_DIR) e file obj)

# Crea la cartella obj
$(OBJ_DIR):
	@mkdir -p $@

# Pulizia
clean:
	@rm -rf $(OBJ_DIR)
	$(call PROGRESS_BAR,\033[31m,Cartella $(OBJ_DIR) pulita!)

fclean: clean
	@rm -f $(NAME)
	$(call PROGRESS_BAR,\033[31m,Eseguibile rimosso!)

re: fclean
	@echo "$(RICOMP)"
	@$(MAKE) --no-print-directory all

.PHONY: all clean fclean re