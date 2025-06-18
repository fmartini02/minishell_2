#************************************************************************************#

.SILENT:

PRINTF = ft_printf/libftprintf.a

GNL = get_next_line/gnl.a

STD_LIB = std_fun/std_lib.a

NAME = libft.a

all: $(NAME)

$(PRINTF):
	make -C ft_printf/

$(GNL):
	make -C get_next_line/

$(STD_LIB):
	make -C std_fun/


$(NAME): $(STD_LIB) $(GNL) $(PRINTF)
	rm -f $(NAME)
	ar -x $(STD_LIB)
	ar -x $(GNL)
	ar -x $(PRINTF)
	ar rc $(NAME) *.o
	rm -f *.o


clean:
	rm -f *.o
	make -C std_fun clean
	make -C get_next_line clean
	make -C ft_printf clean

fclean: clean
	rm -f $(NAME)
	make -C std_fun fclean
	make -C get_next_line fclean
	make -C ft_printf fclean

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus

