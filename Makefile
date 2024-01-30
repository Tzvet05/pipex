# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttrave <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 18:16:33 by ttrave            #+#    #+#              #
#    Updated: 2023/11/29 18:16:37 by ttrave           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAG = -Wall -Wextra -Werror

HEADER = ./pipex.h

HEADER_BONUS = ./pipex_bonus.h

SRC = ft_check_params.c \
	ft_utils.c \
	ft_pipes1.c \
	ft_pipes2.c \
	ft_pipes3.c \
	ft_cmds1.c \
	ft_cmds2.c \
	ft_paths1.c \
	ft_paths2.c \
	pipex.c

SRC_BONUS = ft_check_params_bonus.c \
	ft_utils_bonus.c \
	ft_here_doc_bonus.c \
	ft_file_gen_bonus.c \
	ft_pipes1_bonus.c \
	ft_pipes2_bonus.c \
	ft_pipes3_bonus.c \
	ft_cmds1_bonus.c \
	ft_cmds2_bonus.c \
	ft_paths1_bonus.c \
	ft_paths2_bonus.c \
	pipex_bonus.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)

$(NAME) : libft.a $(OBJ)
	$(CC) $(CFLAG) $(OBJ) libft.a -o $(NAME)

bonus : libft.a $(OBJ_BONUS)
	$(CC) $(CFLAG) $(OBJ_BONUS) libft.a -o $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -c $^ -o $@

libft.a :
	make -C libft/
	mv libft/libft.a ./

fclean : clean
	make fclean -C libft/
	rm -f $(NAME)

clean :
	make clean -C libft/
	rm -f $(OBJ) $(OBJ_BONUS)
	rm -f libft.a

re :	fclean all

.PHONY : all fclean clean re bonus
