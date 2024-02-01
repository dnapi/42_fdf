NAME = fdf

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src/
INC_DIR = include/
#GLFW_DIR = /Users/apimikov/.brew/opt/glfw/lib

SRC_NAMES = main.c init_fdf.c init_fdf_utils.c read_row.c \
					hooks.c error_msg.c set_size.c \
          bresenham.c bresenham_utils.c

CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast

HEADERS	= -I./include -I$(LIBMLX)/include  -I./$(LIBFT_DIR)

LIBMLX	= ./libmlx42
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
MLX	= $(LIBMLX)/build/libmlx42.a

SRCS = $(addprefix $(SRC_DIR), $(SRC_NAMES))
OBJS	= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(SRCS) $(OBJS) $(LIBFT) $(MLX)
	cc $(FLAGS) $(OBJS) $(LIBS) $(HEADERS)  $(LIBFT) -o $(NAME)

%.o: %.c
	cc $(FLAGS) -c $^ -o $@ $(HEADERS)

$(MLX):
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
