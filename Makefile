# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: CTerblanche <1997corry@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/17 11:24:40 by cterblan          #+#    #+#              #
#    Updated: 2020/03/12 23:23:07 by CTerblanche      ###   ########.fr        #
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
SERVER_SRC :=	s_main.c \
				ft_getaddr_IP.c \
				ft_sendall.c \
				s_bindsocket.c \
				s_listen.c \
				s_newclient.c \
				s_recvdata.c \
				s_find_client.c \
				s_msg_send.c \
				s_rmv_client.c \
				ft_cbuf.c \
				ft_read_cmd.c \
				cmd_join.c \
				cmd_msg.c \
				cmd_nick.c \
				cmd_who.c \
				s_channel_ismember.c \
				s_find_nick.c \
				s_status_send.c \
				s_assign_protocol.c
				
CLIENT_SRC :=	c_main.c \
				ft_getaddr_IP.c \
				ft_sendall.c \
				c_getinput.c
				
#ADD SOURCE FILES HERE ^^^
SERVER_OBJ := $(addprefix $(OBJ_DIR)/, $(SERVER_SRC:%.c=%.o))
CLIENT_OBJ := $(addprefix $(OBJ_DIR)/, $(CLIENT_SRC:%.c=%.o))
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

$(SERVER): $(SERVER_OBJ)
	@make all -C $(PRINTF_DIR)/
	@echo "\033[35m\t\t[COMPILING] $@\033"
	@$(CC) -o $@ $(SERVER_OBJ) -I $(INC_DIR) -L $(PRINTF_DIR)/ $(LIB_FLAG)
	@#COMPILE EXECUTABLE ^^^^^
	@#ar rcs $(SERVER).a $(SERVER_OBJ) $(PRINTF_DIR)/obj/*.o^
	@#COMPILE LIBRARY ^^^^^^^
	@echo "\033[32m\t\t[COMPILED SUCCESSFULLY]\033"
	@#DON'T TOUCH ^^^

$(CLIENT): $(CLIENT_OBJ)
	@make all -C $(PRINTF_DIR)/
	@echo "\033[35m\t\t[COMPILING] $@\033"
	@$(CC) -o $@ $(CLIENT_OBJ) -I $(INC_DIR) -L $(PRINTF_DIR)/ $(LIB_FLAG)
	@#COMPILE EXECUTABLE ^^^^^
	@#ar rcs $(CLIENT).a $(CLIENT_OBJ) $(PRINTF_DIR)/obj/*.o^
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
	@echo "\033[31m\t\t[FCLEAN]\t$(CLIENT)\033[0m"
	@rm -f $(CLIENT)
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
