NAME = ../ft_ssl

SRC = main.c

OBJ = $(SRC:.c=.o)

SRC_DIR = ./srcs
OBJ_DIR = ./objs
INC_DIR = ./include

OBJS = $(OBJ:%=$(OBJ_DIR)/%)

INC = ft_ssl_md5.h

HEAD = $(INC_DIR)/$(INC)

OBJ_PATH = $(addprefix $(OBJ_DIR)/,$(SRC":.c=.o))

FLG = -Wall -Werror -Wextra

CC = gcc

all:
	@make $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(FLG) -I $(INC_DIR) -o $@ -c -fPIC $<

$(OBJS): $(HEAD)

$(NAME): $(OBJS)
	$(CC) $(FLG) $(OBJS) -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

