# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/23 21:22:13 by akupriia          #+#    #+#              #
#    Updated: 2018/11/24 17:15:37 by vdzhanaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re mre

CH := checker
PS := push_swap

CH_PATH :=	src/checker/
PS_PATH :=	src/push_swap/


all:
	@ make -C $(CH_PATH)
	@ make -C $(PS_PATH)
	@ ln -fs $(CH_PATH)$(CH) $(CH)
	@ ln -fs $(PS_PATH)$(PS) $(PS)
	@ chmod 744 $(CH) $(PS)

mre:
	@ make mre -C $(CH_PATH)
	@ make mre -C $(PS_PATH)
	@ ln -fs $(CH_PATH)$(CH) $(CH)
	@ ln -fs $(PS_PATH)$(PS) $(PS)
	@ chmod 744 $(CH) $(PS)
clean:
	make clean -C $(CH_PATH)
	make clean -C $(PS_PATH)
fclean:
	make fclean -C $(CH_PATH)
	make fclean -C $(PS_PATH)
	rm -f $(CH) $(PS)
re: fclean all
