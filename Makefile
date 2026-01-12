# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/22 11:34:31 by demane            #+#    #+#              #
#    Updated: 2026/01/12 14:38:05 by demane           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_TMP = .mandatory
BONUS_FILE = .bonus

SRCS_COMMON = error.c exec.c free.c gnl.c gnl_utils.c \
              here_doc.c init.c parse.c path.c process.c utils.c

SRCS_MANDATORY = $(SRCS_COMMON) main_mandatory.c
SRCS_BONUS     = $(SRCS_COMMON) main_bonus.c

OBJS_MANDATORY = $(SRCS_MANDATORY:.c=.o)
OBJS_BONUS     = $(SRCS_BONUS:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
RM = rm -rf

all: $(NAME_TMP)

bonus: $(BONUS_FILE)

$(NAME_TMP): $(OBJS_MANDATORY) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_MANDATORY) $(LIBFT) -o $(NAME)
	@rm -rf $(BONUS_FILE)
	@touch $(NAME_TMP)

$(BONUS_FILE): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME)
	@rm -rf $(NAME_TMP)
	@touch $(BONUS_FILE)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS_MANDATORY) $(OBJS_BONUS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME) $(BONUS_FILE) $(NAME_TMP)

re: fclean all
rebonus: fclean bonus

.PHONY: all bonus clean fclean re rebonus

