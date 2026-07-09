NAME		= cub3D
BONUS_NAME	= cub3D_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Wno-cast-function-type
BONUS_FLAG	= -DBONUS

SRCS_COMMON			= main.c \
					  parsing/parsing.c \
					  parsing/parse_file.c \
					  parsing/parse_header.c \
					  parsing/parse_map.c \
					  rendering/rendering.c \
					  rendering/trace.c \
					  rendering/trace3d.c \
					  rendering/run_dda.c \
					  rendering/fog.c \
					  rendering/draw_col.c \
					  rendering/setup_hooks.c \
					  utils/utils1.c \
					  utils/memory.c \
					  utils/color_utils.c \
					  utils/hook_utils.c

SRCS_MANDATORY_ONLY	= utils/correct_char.c \
					  utils/move.c \
					  rendering/select_texture.c \
					  rendering/trace_minimap.c \
					  rendering/hand_stub.c \
					  rendering/door_stub.c \
					  rendering/mouse_stub.c \
					  rendering/cleanup_stub.c

SRCS_BONUS_ONLY		= bonus/correct_char_bonus.c \
					  bonus/move_bonus.c \
					  bonus/select_texture_bonus.c \
					  bonus/minimap_bonus.c \
					  bonus/hand_bonus.c \
					  bonus/door_bonus.c \
					  bonus/mouse_bonus.c \
					  bonus/cleanup_bonus.c

SRCS_MANDATORY	= $(SRCS_COMMON) $(SRCS_MANDATORY_ONLY)
SRCS_BONUS		= $(SRCS_COMMON) $(SRCS_BONUS_ONLY)

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

OBJ_DIR_MANDATORY	= objects_mandatory
OBJ_DIR_BONUS		= objects_bonus

MLX_PATH	= minilibx-linux
MLX_FLAGS	= -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lbsd
INCLUDES	= -I. -I$(MLX_PATH)

OBJS_MANDATORY	= $(addprefix $(OBJ_DIR_MANDATORY)/, $(SRCS_MANDATORY:.c=.o))
OBJS_BONUS		= $(addprefix $(OBJ_DIR_BONUS)/, $(SRCS_BONUS:.c=.o))

all: $(NAME)

bonus: $(BONUS_NAME)

$(LIBFT):
	@echo "=== Building libft ==="
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS_MANDATORY)
	$(CC) $(CFLAGS) $(OBJS_MANDATORY) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(BONUS_NAME): $(LIBFT) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(BONUS_FLAG) $(OBJS_BONUS) $(LIBFT) $(MLX_FLAGS) -o $(BONUS_NAME)

$(OBJ_DIR_MANDATORY)/%.o: %.c cub3D.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: %.c cub3D.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(BONUS_FLAG) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR_MANDATORY) $(OBJ_DIR_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

re-bonus: fclean bonus

.PHONY: all bonus clean fclean re re-bonus