# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 14:45:02 by igilani           #+#    #+#              #
#    Updated: 2025/02/23 13:46:41 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -c
NAME    = tha_supreme_lib.a
OBJ_DIR = obj
OBJ     = $(addprefix $(OBJ_DIR)/, $(SRC_LIBFT:.c=.o) $(SRC_FT_PRINTF:.c=.o) $(SRC_GET_NEXT_LINE:.c=.o))
RICOMP  = $(YELLOW)[$(RESET)$(BLUE)=====$(RESET)$(GREEN)RICOMPILO$(RESET)$(BLUE)=====$(RESET)$(YELLOW)]$(RESET)

RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RESET   = \033[0m

all: $(NAME)
	$(call PROGRESS_BAR_END,\033[32m,Libreria \033[33mtha_supreme.a\033[0m \033[32mgenerata)

SRC_LIBFT =	Libft/ft_isalpha.c Libft/ft_isdigit.c Libft/ft_isalnum.c Libft/ft_isascii.c Libft/ft_isprint.c \
			Libft/ft_strlen.c Libft/ft_memset.c Libft/ft_bzero.c Libft/ft_memcpy.c Libft/ft_memmove.c \
			Libft/ft_strlcpy.c Libft/ft_strlcat.c Libft/ft_toupper.c Libft/ft_tolower.c Libft/ft_strchr.c \
			Libft/ft_strrchr.c Libft/ft_memchr.c Libft/ft_strncmp.c Libft/ft_memcmp.c Libft/ft_strnstr.c \
			Libft/ft_atoi.c Libft/ft_calloc.c Libft/ft_strdup.c Libft/ft_substr.c Libft/ft_strjoin.c \
			Libft/ft_strtrim.c Libft/ft_split.c Libft/ft_itoa.c Libft/ft_strmapi.c Libft/ft_striteri.c \
			Libft/ft_putchar_fd.c Libft/ft_putstr_fd.c Libft/ft_putendl_fd.c Libft/ft_putnbr_fd.c Libft/ft_putnbr_base_fd.c\
			Libft/ft_lstnew.c Libft/ft_lstadd_front.c Libft/ft_lstsize.c Libft/ft_lstlast.c Libft/ft_utoa.c Libft/ft_atodbl.c\
			Libft/ft_lstadd_back.c Libft/ft_lstdelone.c Libft/ft_lstclear.c Libft/ft_lstiter.c Libft/ft_lstmap.c

SRC_FT_PRINTF = ft_printf/ft_printf.c ft_printf/ft_check/case_int.c ft_printf/ft_check/case_void.c \
				ft_printf/ft_check/case_unsigned.c ft_printf/ft_check/case_char.c ft_printf/ft_printf.c

SRC_GET_NEXT_LINE = get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c

$(OBJ_DIR):
	@mkdir -p $@
	$(call PROGRESS_BAR_START)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call PROGRESS_BAR_UPDATE)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	$(call PROGRESS_BAR_UPDATE)

clean:
	@rm -rf $(OBJ_DIR)
	$(call PROGRESS_BAR,\033[31m,Cartella $(OBJ_DIR) pulita!)

fclean: clean
	@rm -f $(NAME)
	$(call PROGRESS_BAR,\033[31m,Libreria eliminata!)

re: fclean
	@echo "$(RICOMP)"
	@$(MAKE) --no-print-directory all

.PHONY: all clean fclean re