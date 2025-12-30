# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/22 11:34:31 by demane            #+#    #+#              #
#    Updated: 2025/12/30 15:18:42 by demane           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BONUS = pipex_bonus
NAME_MANDATORY = pipex

SRCS = error.c exec.c free.c get_next_line.c get_next_line_utils.c \
			here_doc.c init.c main_mandatory.c parse.c path.c process.c utils.c

SRCS_BONUS = error.c exec.c free.c get_next_line.c get_next_line_utils.c \
			here_doc.c init.c main_bonus.c parse.c path.c process.c utils.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc -I.

RM = rm -rf

FLAGS = -Wall -Wextra -Werror

all : $(NAME_MANDATORY)

bonus: $(NAME_BONUS)

$(NAME_MANDATORY): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS)  $(OBJS) $(LIBFT) -o $(NAME_MANDATORY)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(FLAGS)  $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)

$(LIBFT):
	make --directory=$(LIBFT_DIR)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	make --directory=$(LIBFT_DIR) clean
	$(RM) $(OBJS_BONUS) $(OBJS)

fclean: clean
	make --directory=$(LIBFT_DIR) fclean
	$(RM) $(NAME_BONUS) $(NAME_MANDATORY)

re: fclean all

rebonus: fclean bonus

.PHONY: all re fclean bonus clean
