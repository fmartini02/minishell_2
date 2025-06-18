.SILENT:

SRC = main_bonus.c \
	flag_dot/dot_int_case.c \
	flag_dot/dot_int_neg_case.c \
	flag_dot/dot_uns_case.c \
	flag_dot/dot_uns_neg_case.c \
	flag_dot/dot_utils.c \
	flag_dot/handle_dot_case.c \
	flag_dot/spec_dot_case.c \
	flag_dot/spec_dot_neg_case.c \
	\
	flag_pos/handle_pos.c \
	flag_pos/pos_num_case.c \
	flag_pos/pos_case.c \
	flag_pos/pos_num_case.c \
	flag_pos/neg_pos_case.c \
	flag_pos/neg_pos_num_case.c \
	\
	flag_space/handle_space.c \
	flag_space/space_num_utils.c \
	flag_space/space_utils.c \
	\
	flag_width/handle_width.c \
	flag_width/neg_width_num_utils.c \
	flag_width/neg_width_utils.c \
	flag_width/width_num_utils.c \
	flag_width/width_utils.c \
	\
	flag_zero/handle_zero.c \
	flag_zero/neg_zero_addr.c \
	flag_zero/neg_zero_num.c \
	flag_zero/zero_addr.c \
	flag_zero/zero_num.c \
	\
	basic_fun_bonus.c \
	bonus_utils.c \
	handle_sharp.c \
	mandatory_utils_bonus.c \

OBJS = $(SRC:.c=.o)

NAME = libftprintf.a

CC = clang

RM = rm -f

FLAGS = -Werror -Wall -Wextra -g

MAKE := make

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re exe bonus
