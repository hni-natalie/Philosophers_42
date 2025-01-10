# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/26 11:14:33 by hni-xuan          #+#    #+#              #
#    Updated: 2025/01/09 18:19:45 by hni-xuan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
CFLAGS = -Wall -Wextra -Werror -g

OBJS_DIR = objs
SRCS_FILES = main utils routine dining

SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(SRCS_FILES)))
OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(SRCS_FILES)))

NAME = philo

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@ -lpthread

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	
clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -rf $(OBJS_DIR) $(NAME)

re: fclean all

.PHONY: all cealn fclean re

