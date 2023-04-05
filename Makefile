##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## makefile
##

SRC1 = $(shell find src/server/*.c)

SRC2 = $(shell find src/client/*.c)

BIN_SERVER = myteams_server
LIB = -L./libs/myteams -lmyteams
BIN_CLIENT = myteams_cli
INCLUDE = -I./include -I./libs/myteams

# export LD_LIBRARY_PATH=/home/grafox/TEK2/NWP/B-NWP-400-MAR-4-1-myteams-niels.ouvrard/libs/myteams
# export LD_LIBRARY_PATH=/home/morais/delivery/myteams/B-NWP-400-MAR-4-1-myteams-niels.ouvrard/libs/myteams

all: client server

client:
	gcc $(SRC2) -o $(BIN_CLIENT) $(INCLUDE) -g3 $(LIB) -DSQLITE_THREADSAFE=0

server:
	gcc $(SRC1) -o $(BIN_SERVER) $(INCLUDE) -luuid -lsqlite3 -g3 $(LIB) -DSQLITE_THREADSAFE=0

clean:
	$rm -rf $(BIN_CLIENT)
	rm -rf $(BIN_SERVER)

fclean:
	rm -rf $(BIN_CLIENT)
	rm -rf $(BIN_SERVER)
	rm -rf *.o
	rm -rf vgcore*
	rm -rf data/users/*

re: fclean all client server
