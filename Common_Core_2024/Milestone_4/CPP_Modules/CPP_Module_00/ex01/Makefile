# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/26 17:28:53 by igilani           #+#    #+#              #
#    Updated: 2025/08/04 16:15:48 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = phonebook
SRC = contact.cpp phonebook.cpp main.cpp

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

#Colori ANSI
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RESET = \033[0m

all:
	@$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)
	@echo "$(GREEN)✔ Eseguibile $(YELLOW)$(NAME)$(RESET) $(GREEN)generato$(RESET)"

clean:
	@rm -f $(NAME)
	@echo "$(BLUE)➜ Eseguibile $(YELLOW)$(NAME)$(RESET) $(BLUE)rimosso$(RESET)"

re: clean all

.PHONY: all clean re