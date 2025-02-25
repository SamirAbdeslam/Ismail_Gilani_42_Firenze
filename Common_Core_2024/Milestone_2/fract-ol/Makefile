# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 19:13:20 by igilani           #+#    #+#              #
#    Updated: 2025/02/25 13:14:21 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Configurazioni principali
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -o3
NAME    = fractol
SRC     = fractol.c render.c math_utils.c event_control.c
HEADERS = fractol.h
OBJ_DIR = obj
OBJ     = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
LIB_DIR = tha_supreme_lib
MLX_DIR = minilibx-linux

# Colori ANSI
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RESET   = \033[0m

# Progress bar migliorata
define PROGRESS_BAR
	printf "$(YELLOW)[$(RESET)$(BLUE)%s$(YELLOW)]$(RESET) Compilato %s\n" "$(shell printf '=%.0s' $(shell seq 1 $(shell expr $(1) \* 20 / $(TOTAL))))" "$2"
endef

TOTAL := $(words $(SRC))
COUNT := 0

# Regole principali
all: $(NAME)
	@if [ $(COUNT) -eq 0 ] && [ ! -n "$(REBUILD_LIBS)" ]; then \
        echo "$(BLUE)✓ Nessuna modifica rilevata. Programma già compilato.$(RESET)"; \
    else \
        echo "$(GREEN)✔ Build completato$(RESET)"; \
    fi

# Timestamp files for libraries
LIB_TIMESTAMP = $(LIB_DIR)/.timestamp
MLX_TIMESTAMP = $(MLX_DIR)/.timestamp

$(NAME): $(OBJ) | lib_check
	@if [ ! -f $@ ] || [ -n "$(shell find $^ -newer $@)" ]; then \
        $(CC) $(CFLAGS) $^ -o $@ $(MLX_DIR)/libmlx_Linux.a -L$(LIB_DIR) -l:tha_supreme_lib.a -lm -lX11 -lXext; \
        echo "$(GREEN)✔ Eseguibile $(NAME) generato$(RESET)"; \
    fi

# Check if libraries need rebuilding
lib_check:
    @REBUILD_LIBS=0; \
    if [ ! -f $(LIB_TIMESTAMP) ]; then \
        $(MAKE) -s -C $(LIB_DIR); \
        touch $(LIB_TIMESTAMP); \
        REBUILD_LIBS=1; \
    fi; \
    if [ ! -f $(MLX_TIMESTAMP) ]; then \
        $(MAKE) -s -C $(MLX_DIR); \
        touch $(MLX_TIMESTAMP); \
        REBUILD_LIBS=1; \
    fi; \
    if [ "$$REBUILD_LIBS" = "1" ]; then \
        export REBUILD_LIBS=1; \
    fi

# Old libs target for compatibility
libs: lib_check

# Regola per i file oggetto
$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@if [ ! -f $@ ] || [ $< -nt $@ ] || [ -n "$(shell find $(HEADERS) -newer $@ 2>/dev/null)" ]; then \
        $(eval COUNT := $(shell expr $(COUNT) + 1)) \
        $(CC) $(CFLAGS) -c $< -o $@; \
        $(call PROGRESS_BAR,$(COUNT),"$<"); \
    fi

$(OBJ_DIR):
	@mkdir -p $@

# Pulizia
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIB_DIR) clean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@echo "$(RED)✔ Cartella $(OBJ_DIR) pulita$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIB_DIR) fclean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@echo "$(RED)✔ Eseguibile $(NAME) rimosso$(RESET)"

re: fclean all

.PHONY: all clean fclean re libs