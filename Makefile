NAME = Game

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src/
INC_DIR = include/

SRC_NAMES = main.c get_next_line.c get_next_line_utils.c

CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast

HEADERS	= -I./include -I $(LIBMLX)/include  -I./libft

#LIBMLX	= ./mlx42
#LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS = $(addprefix $(SRC_DIR), $(SRC_NAMES))
OBJS	= ${SRCS:.c=.o}

#all: libmlx $(NAME)
all: $(NAME)

#libmlx:
#	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)


# $(NAME): $(OBJS)
# 	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	cc $(FLAGS) $(OBJS) $(LIBFT) $(HEADERS) -o $(NAME)

%.o: %.c
	cc $(FLAGS) -c $^ -o $@ $(HEADERS)
#	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

clean:
	@rm -rf $(OBJS)
#	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
