# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/26 17:28:53 by igilani           #+#    #+#              #
#    Updated: 2025/07/29 13:23:28 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = account
SRC = Account.cpp tests.cpp

all:
	c++ -Wall -Wextra -Werror -std=c++98 $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re