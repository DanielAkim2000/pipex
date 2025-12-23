# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/22 11:34:31 by demane            #+#    #+#              #
#    Updated: 2025/12/22 12:11:28 by demane           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BONUS = pipex

SRCS_BONUS = error.c exec.c free.c get_next_line.c get_next_line_utils.c \
			here_doc.c init.c main.c parse.c path.c pipe.c utils.c

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc -I.

RM = rm -rf

FLAGS = -Wall -Wextra -Werror

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(FLAGS)  $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)

$(LIBFT):
	make --directory=$(LIBFT_DIR)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME_BONUS)

re: bonus clean fclean

.PHONY: all re fclean bonus clean
