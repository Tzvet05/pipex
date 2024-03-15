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

# Make parameters

NAME = pipex

COMPILER = cc

CFLAG = -Wall -Wextra -Werror

LIB = libft.a

# Directories

LIB_DIR =	libft/
HDR_DIR =	hdr/
SRC_DIR =	src/
OBJ_DIR =	obj/
SRC_BONUS_DIR =	src_bonus/
OBJ_BONUS_DIR =	obj_bonus/

# Source code (mandatory)

SRC =	ft_check_params.c \
	ft_utils.c \
	ft_pipes1.c \
	ft_pipes2.c \
	ft_pipes3.c \
	ft_cmds1.c \
	ft_cmds2.c \
	ft_paths1.c \
	ft_paths2.c \
	pipex.c

# Source code (bonus)

SRC_BONUS =	ft_check_params_bonus.c \
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

# Compiled objects (mandatory)

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Compiled objects (bonus)

OBJ_BONUS = $(addprefix $(OBJ_BONUS_DIR), $(SRC_BONUS:.c=.o))

# Compilation (mandatory)

$(NAME) : $(LIB) $(OBJ)
	@ echo "$(NAME) compiled (mandatory)."
	@ $(COMPILER) $(CFLAG) $(OBJ) $(LIB) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	@ $(COMPILER) $(CFLAG) -I $(HDR_DIR) -c $^ -o $@

# Compilation (bonus)

bonus : $(LIB) $(OBJ_BONUS)
	@ echo "$(NAME) compiled (bonus)."
	@ $(COMPILER) $(CFLAG) $(OBJ_BONUS) $(LIB) -o $(NAME)

$(OBJ_BONUS_DIR)%.o : $(SRC_BONUS_DIR)%.c | $(OBJ_BONUS_DIR)
	@ $(COMPILER) $(CFLAG) -I $(HDR_DIR) -c $^ -o $@

# Objects directories

$(OBJ_DIR) $(OBJ_BONUS_DIR) :
	@ mkdir -p $@

# Library

$(LIB) :
	@ make -s -C $(LIB_DIR)
	@ mv $(LIB_DIR)$(LIB) .

# Rules

all : $(NAME)

fclean : clean
	@ make fclean -s -C $(LIB_DIR)
	@ rm -f $(NAME) $(NAME_BONUS)

clean :
	@ make clean -s -C $(LIB_DIR)
	@ rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@ rm -f $(LIB)

re : fclean all

.PHONY : all fclean clean re bonus
