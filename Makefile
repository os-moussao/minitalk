CLI = client
SER = server
LIBDIR = printf/
LIB = $(LIBDIR)libftprintf.a
PRINTF = ftprintf

RM = rm -f
CC = cc
CFLAGS = -Wall -Werror -Wextra

all: $(CLI) $(SER)

$(LIB):
	make -C $(LIBDIR) bonus
	make -C $(LIBDIR) clean

$(CLI): client.c $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L$(LIBDIR) -l$(PRINTF)

$(SER): server.c $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L$(LIBDIR) -l$(PRINTF)

clean:
	# $(RM) $(CLI) $(SER)

fclean: clean
	make -C $(LIBDIR) fclean

re: fclean all
