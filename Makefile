NAME = librt.a
CFLAGS = -Wall -Wextra -Werror
LEAKLAGS = -g -fsanitize=address
SOURCE = utils_gnl.c \
	utils_function.c \
	utils_atoi.c \
	utils_atof.c \
	utils_split_space.c \
	utils_split_comma.c \
	utils_vector1.c \
	utils_vector2.c \
	utils_vector3.c \
	utils_ray1.c \
	utils_light1.c \
	utils_light2.c \
	utils_light3.c \
	utils_init1.c \
	utils_set1.c \
	utils_set2.c \
	utils_event1.c \
	utils_bmp1.c \
	utils_draw1.c \
	utils_draw2.c \
	utils_hit1.c \
	utils_hit2.c \
	utils_hit3.c \
	utils_hit4.c \
	utils_check1.c \
	utils_check2.c \
	utils_check3.c \
	utils_check4.c \
	utils_check5.c
MAIN = main.c
LIBFT_PATH = libft_rt
MLX_PATH = minilibx_mms
MLX_NAME = libmlx.dylib
L_MLX_D = -L. -lmlx
L_MLX_A = -L. -lrt
L_LIBFT = -L./$(LIBFT_PATH) -lft
OUT = minirt
BMP = jwoo.bmp
OBJECT = $(SOURCE:.c=.o)
$(NAME): $(OBJECT)
	make -C ./$(LIBFT_PATH) all
	make -C ./$(MLX_PATH) all
	cp $(MLX_PATH)/$(MLX_NAME) $(MLX_NAME)
	ar	rcs $(NAME) $(OBJECT)
	gcc $(MAIN) $(CFLAGS) $(L_MLX_D) $(L_MLX_A) $(L_LIBFT) -o $(OUT)
$(OBJECT): $(SOURCE)
	gcc $(CFLAGS) -c $(SOURCE)
all : $(NAME)
clean:
	@make -C ./$(LIBFT_PATH) clean
	@make -C ./$(MLX_PATH) clean
	@rm -f *.o
fclean:
	@make -C ./$(LIBFT_PATH) fclean
	@make -C ./$(MLX_PATH) clean
	@rm -f *.o
	@rm -f librt.a
	@rm -f libmlx.dylib
	@rm -f minirt
	@rm -f jwoo.bmp
re:	fclean all
.PHONY: all clean fclean re