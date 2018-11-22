# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/21 07:33:21 by vdzhanaz          #+#    #+#              #
#    Updated: 2018/11/21 17:19:40 by vdzhanaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re mclean mfclean mre test

NAME		:=	push_swap

SRC_PATH	:=	src/
INC_PATH	:=	includes/
LIB_PATH	:=	ft_printf/
LIB			:=	$(LIB_PATH)libftprintf.a
OBJ_PATH	:=	.obj/

CC			:=	clang
CFLAGS		:=	-g -Wall -Werror -Wextra
IFLAGS		:=	-I $(INC_PATH) -I $(LIB_PATH)
LFLAGS		:=	-lftprintf -L $(LIB_PATH)

HFILES		:=	push_swap
FILES		:=	push_swap

HDRS := $(addprefix $(INC_PATH), $(addsuffix .h, $(HFILES)))
SRCS := $(addprefix $(SRC_PATH), $(addsuffix .c, $(FILES)))
OBJS := $(addprefix $(OBJ_PATH), $(SRCS:%.c=%.o))


all: $(NAME)

$(NAME): $(LIB) $(OBJ_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)
$(LIB):
	make -C $(LIB_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)$(SRC_PATH)
$(OBJ_PATH)%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean: mclean
	make clean -C $(LIB_PATH)
fclean: mfclean
	make fclean -C $(LIB_PATH)
re: fclean all

mclean:
	rm -f $(OBJS) $(DEPS)
mfclean:
	rm -f $(NAME)
	rm -rf $(OBJ_PATH)
mre: mfclean all
