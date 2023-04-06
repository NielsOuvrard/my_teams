##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## makefile
##

SRC1 = $(shell find src/server/*.c)

SRC2 = $(shell find src/client/*.c)

#include <uuid.,>

BIN_SERVER = myteams_server
LIB = -L./libs/myteams -lmyteams -lsqlite3
BIN_CLIENT = myteams_cli
INCLUDE = -I./include -I./libs/myteams
SQL = -DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_DEPRECATED -DSQLITE_THREAD_OVERRIDE_LOCK=-1

all: client server

client:
	gcc $(SRC2) -o $(BIN_CLIENT) $(INCLUDE) -g3 $(LIB) $(SQL)

server:
	gcc $(SRC1) -o $(BIN_SERVER) $(INCLUDE) -luuid -g3 $(LIB) $(SQL)

clean:
	rm -rf $(BIN_CLIENT)
	rm -rf $(BIN_SERVER)

fclean:
	rm -rf $(BIN_CLIENT)
	rm -rf $(BIN_SERVER)
	rm -rf *.o
	rm -rf vgcore*
	rm -rf data/users/*

re: fclean all client server
