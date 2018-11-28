# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/23 21:00:30 by akupriia          #+#    #+#              #
#    Updated: 2018/11/26 18:15:11 by vdzhanaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re mclean mfclean mre

NAME	:=	checker
LIB		:=	../../ft_printf/
LIB_N	:=	$(LIB)libftprintf.a

INC_D	:=	../../includes/
SRC_D	:=	./
OBJ_D	:=	.obj/

CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror
IFLAGS	:=	-I $(INC_D) -I $(LIB)
LFLAGS	:=	-L $(LIB) -lftprintf

SRC		:=	checker checker_op ps_sup_functions
SRCS	:=	$(addprefix $(SRC_D), $(addsuffix .c, $(SRC)))
OBJS	:=	$(addprefix $(OBJ_D), $(SRCS:%.c=%.o))
HDRS	:=	$(wildcard $(INC_D)*.h)

all: $(NAME)

$(NAME): $(LIB_N) $(OBJ_D) $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)
$(LIB_N):
	make -C $(LIB)

$(OBJ_D):
	mkdir -p $(OBJ_D)$(SRC_D)
$(OBJ_D)%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

mclean:
	rm -rf $(OBJ_D)
mfclean: mclean
	rm -f $(NAME)
mre: mfclean all

clean:
	make clean -C $(LIB)
	rm -rf $(OBJ_D)
fclean: clean
	make fclean -C $(LIB)
	rm -f $(NAME)
re: fclean all
