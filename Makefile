RM = rm -f
CC = cc
CFLAGS = -Wall -Werror -Wextra

LIBDIR = printf/
LIB = $(LIBDIR)libftprintf.a
PRINTF = ftprintf

OBJ := client.o server.o

all: client server

$(LIB):
	make -C $(LIBDIR) bonus
	make -C $(LIBDIR) clean

client: client.o $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L$(LIBDIR) -l$(PRINTF)

server: server.o $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L$(LIBDIR) -l$(PRINTF)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) client server
	make -C $(LIBDIR) fclean

re: fclean all
