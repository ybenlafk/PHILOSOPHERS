# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 13:54:20 by ybenlafk          #+#    #+#              #
#    Updated: 2023/03/08 17:57:04 by ybenlafk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

HEADER= philo.h

SRCS= strjoin.c  utilis_1.c utilis.c ft_split.c parsing.c \
		routine.c new_philo.c	main.c

OBGJ= $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
FRM = rm -rf

all: $(NAME)

$(NAME): $(OBGJ)
	$(CC) $(CFLAGS) $(OBGJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(FRM) $(OBGJ) 

fclean: clean
	$(FRM) $(NAME)

re: fclean all

.PHONY: all clean fclean re