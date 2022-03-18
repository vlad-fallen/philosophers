# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 15:40:50 by mbutter           #+#    #+#              #
#    Updated: 2022/03/18 20:23:53 by mbutter          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCS		=	philo_bonus.c \
				parse_bonus.c \
				init_philo_bonus.c \
				life_of_philo_bonus.c \
				check_death_bonus.c \
				utils_bonus.c

OBJS		=	$(patsubst %.c,%.o,$(SRCS)) 

BONUS		=	

BONUS_OBJS	=	$(patsubst %.c,%.o,$(BONUS))

D_FILES		=	$(patsubst %.c,%.d,$(SRCS) $(BONUS)) 

CC			=	gcc

RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror -g -pthread

%.o:		%.c Makefile
			$(CC) $(CFLAGS) -c $< -o $@ -MMD

$(NAME):	$(OBJS) Makefile 
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -MMD

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(D_FILES) $(BONUS_OBJS) $(D_FILES_B)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re bonus

include $(wildcard $(D_FILES))
