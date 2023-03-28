NAME_C	=	client

NAME_S	=	server

INCLUDE	=	includes/

SRC_DIR	=	srcs/

CC		=	gcc

BUILD	=	.build/

CFLAGS	=	-Wall -Werror -Wextra

SRC_C	=	client.c

OBJ_C	=	$(SRC_C:.c=.o)

SRC_S	=	server_0.c	\
			server_1.c

OBJ_S	=	$(SRC_S:.c=.o)

all:	$(BUILD) $(NAME_C) $(NAME_S)

$(BUILD):
	mkdir .build

$(BUILD)%.o:	$(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I./$(INCLUDE)

$(NAME_C):	$(addprefix $(BUILD), $(OBJ_C))
	$(CC) $(CFLAGS) $(addprefix $(BUILD), $(OBJ_C)) -o $(NAME_C) -I/$(INCLUDE)

$(NAME_S):	$(addprefix $(BUILD), $(OBJ_S))
	$(CC) $(CFLAGS) $(addprefix $(BUILD), $(OBJ_S)) -o $(NAME_S) -I/$(INCLUDE)

clean:
	rm -f $(addprefix $(BUILD), $(OBJ_S)) $(addprefix $(BUILD), $(OBJ_C))

fclean:	clean rmbuild
	rm -f $(NAME_C) $(NAME_S)
	
rmbuild: 
	rm -rf .build

re: fclean all

.PHONY: re fclean all clean rmbuild