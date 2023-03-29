##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## makefile
##

SRC1 = $(shell find src/server/*.c)

SRC2 = $(shell find src/client/*.c)

NAME1 = myteams_server

NAME2 = myteams_cli

all:
	gcc $(SRC1) -o $(NAME1) -I./include -luuid -g3
	gcc $(SRC2) -o $(NAME2) -I./include

clean:
	rm -rf $(NAME1)
	rm -rf $(NAME2)

fclean:
	rm -rf $(NAME1)
	rm -rf $(NAME2)
	rm -rf *.o
	rm -rf vgcore*

re: fclean all
