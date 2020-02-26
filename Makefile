# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cterblan <cterblan@student.wethinkcode>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/17 11:24:40 by cterblan          #+#    #+#              #
#    Updated: 2018/09/06 15:28:19 by cterblan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#								NAME
################################################################################
AUTHOR := cterblan
#AUTHOR NAME^^^

SERVER := server
CLIENT := client
#PROJECT OUTPUT FILE NAME ^^^
################################################################################
#								DIRECTORIES
################################################################################
INC_DIR := inc
#INCLUDES DIRECTORY ^^^
SRC_DIR := src
#SOURCES DIRECTORY ^^^
OBJ_DIR := obj
#OBJECTS DIRECTORY ^^^
LIB_DIR := lib
#LIBRARY DIRECTORY ^^^
################################################################################
#								FILES
################################################################################
#SRC:= ft_function.c
SERVER_SRC :=	server_main.c \
				server_bindaddr.c \
				server_getaddrinfo.c \
				server_readdatagram.c \
				server_launchmessage.c
CLIENT_SRC :=	client_main.c
#ADD SOURCE FILES HERE ^^^
OBJ := $(addprefix $(OBJ_DIR)/, $(SERVER_SRC:%.c=%.o))
################################################################################
#								LIBRARIES
################################################################################
#NAME_DIR := $(LIBDIR)/{library}
PRINTF_DIR := $(LIB_DIR)/printf
#ADD ADDITIONAL LIBRARIES HERE ^^^
LIB_FLAG := -lftprintf
################################################################################
#								COMPILER
################################################################################
CFLAGS := -Wall -Werror -Wextra -D_XOPEN_SOURCE=500 -g
#ADD ADDITIONAL FLAGS HERE ^^^
CC := gcc $(CFLAGS)
################################################################################
#								RULES
################################################################################

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ)
	@make all -C $(PRINTF_DIR)/
	@echo "\033[35m\t\t[COMPILING] $@\033"
	@$(CC) -o $@ $(OBJ) -I $(INC_DIR) -L $(PRINTF_DIR)/ $(LIB_FLAG)
	@#COMPILE EXECUTABLE ^^^^^
	@#ar rcs $(SERVER).a $(OBJ) $(PRINTF_DIR)/obj/*.o^
	@#COMPILE LIBRARY ^^^^^^^
	@echo "\033[32m\t\t[COMPILED SUCCESSFULLY]\033"
	@#DON'T TOUCH ^^^

$(CLIENT): $(OBJ)
	@make all -C $(PRINTF_DIR)/
	@echo "\033[35m\t\t[COMPILING] $@\033"
	@$(CC) -o $@ $(OBJ) -I $(INC_DIR) -L $(PRINTF_DIR)/ $(LIB_FLAG)
	@#COMPILE EXECUTABLE ^^^^^
	@#ar rcs $(SERVER).a $(OBJ) $(PRINTF_DIR)/obj/*.o^
	@#COMPILE LIBRARY ^^^^^^^
	@echo "\033[32m\t\t[COMPILED SUCCESSFULLY]\033"
	@#DON'T TOUCH ^^^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "\033[36m\t\t[Building]\033[0m $@"
	@mkdir -p $(OBJ_DIR)
	@$(CC) -I $(INC_DIR) -o $@ -c $<
	@echo "\033[33m\t\t[SUCCESS]\033[0m"
	@#DON'T TOUCH ^^^

clean: cleanlib
	@echo "\033[31m\t\t[CLEANING]\t$(OBJ_DIR)\033[0m"
	@rm -rf $(OBJ_DIR)
	@#DON'T TOUCH ^^^

cleanlib:
	@echo "\033[31m\t\t[CLEANING]\t$(PRINTF_DIR)\033[0m"
	@make clean -C $(PRINTF_DIR)
	@#ADD ADDITIONAL LIBRARIES HERE ^^^

fclean: clean fcleanlib
	@echo "\033[31m\t\t[FCLEAN]\t$(SERVER)\033[0m"
	@rm -f $(SERVER)
	@#ADD ADDITIONAL NAME FILES HERE ^^^

fcleanlib:
	@echo "\033[31m\t\t[FCLEAN]\t$(PRINTF_DIR)]\033[0m"
	@make fclean -C $(PRINTF_DIR)
	@#ADD ADDITIONAL LIBRARIES HERE ^^^

re: fclean all

update:
	git submodule update --init --recursive --remote

workspace:
	@echo "\033[36m\t\t[Building $@]\033[0m"
	@mkdir -p $(INC_DIR)
	@mkdir -p $(SRC_DIR)
	@mkdir -p $(LIB_DIR)
	@mkdir -p resources
	@touch ./resources/references
	@touch author
	@echo $(AUTHOR) > author
################################################################################
#								SPECIAL
################################################################################

.PHONEY := all clean fclean re workspace test update
#ADD PHONEY HERE ^^^

.SILENT:
#DON'T TOUCH ^^^

.PRECIOUS := author
#ADD PRECIOUS HERE ^^^
