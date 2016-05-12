##
## Makefile for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp
## 
## Made by Guillaume PROQUIN
## Login   <proqui_g@epitech.net>
## 
## Started on  Sat May  7 17:40:43 2016 Guillaume PROQUIN
## Last update Thu May 12 14:46:53 2016 Guillaume PROQUIN
##

NAME		= server

SRC		= src/my_ftp.c		\
		src/parser.c		\
		src/cmd.c		\
		src/client.c		\
		src/fn_dir.c		\
		src/fn_client.c		\
		src/get_next_line.c

OBJ		= $(SRC:.c=.o)

CFLAGS		= -W -Wall -Werror -Wextra -I include/

CC		= gcc

RM		= rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

dbg:		CFLAGS += -g
dbg:		re
