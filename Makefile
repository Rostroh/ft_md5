NAME = ./ft_ssl

SRC = main.c block_parser.c errors_input.c flags.c ft_md5.c ft_sha256.c dispencer.c md5_func.c output.c reader.c

OBJ = $(SRC:.c=.o)

SRC_DIR = ./srcs
OBJ_DIR = ./objs
INC_DIR = ./include

OBJS = $(OBJ:%=$(OBJ_DIR)/%)

INC = ft_ssl.h

HEAD = $(INC_DIR)/$(INC)

LIBFT = libft.a
LIB_DIR = ./libft
LFT = $(LIB_DIR)/$(LIBFT)
LIB = -L $(LIB_DIR) -l$(LIBFT:lib%.a=%)

OBJ_PATH = $(addprefix $(OBJ_DIR)/,$(SRC":.c=.o))

FLG = #-Wall -Werror -Wextra

CC = gcc

all:
	@make -C $(LIB_DIR)
	@make $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(FLG) -I $(INC_DIR) -o $@ -c -fPIC $<

$(OBJS): $(HEAD)

$(NAME): $(OBJS)
	$(CC) $(FLG) $(OBJS) -o $@ $(LIB)

clean:
	@rm -rf $(OBJ_DIR)
	@make $@ -C $(LIB_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make $@ -C $(LIB_DIR)

re: fclean all

