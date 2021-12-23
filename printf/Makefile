#
# names
#
NAME := libftprintf.a

AR := ar -crs

RM := rm -rf

CC := gcc

CFLAGS := -Wall -Werror -Wextra

#
# rules not to mixed with similar file names
#
.PHONY: all bonus clean fclean re

#
# directories
#
INCLUDE := includes/

SRCS_DIR := srcs/

#
# necessary files
#
CFILES := parser.c print_format.c print_string.c print_number.c utils.c
HFILES := $(INCLUDE)ft_printf.h

SRCS := $(addprefix $(SRCS_DIR), $(CFILES) ft_printf.c)
SRCSB := $(addprefix $(SRCS_DIR), $(CFILES) ft_printf_bonus.c)

OBJS := $(SRCS:.c=.o)
OBJSB := $(SRCSB:.c=.o)

#
# rules
#
all: $(NAME)

bonus: $(OBJSB)
	$(AR) $(NAME) $^

$(NAME): $(OBJS) 
	$(AR) $@ $^

%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) -c $< -I$(INCLUDE) -o $@

clean:
	$(RM) $(sort $(OBJS) $(OBJSB))

fclean: clean
	$(RM) $(NAME)

re: fclean all
