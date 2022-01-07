RM = rm -f
CC = cc
CFLAGS = -Wall -Werror -Wextra

LIBDIR = printf/
LIB = $(LIBDIR)libftprintf.a
PRINTF = ftprintf

OBJ := client.o server.o client_bonus.o server_bonus.o

all: client server

bonus: client_bonus server_bonus

$(LIB):
	make -C $(LIBDIR) bonus
	make -C $(LIBDIR) clean

client: client.o $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L$(LIBDIR) -l$(PRINTF)

server: server.o $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L$(LIBDIR) -l$(PRINTF)

client_bonus: client_bonus.o $(LIB)
	$(CC) $(CFLAGS) -o client $< -L$(LIBDIR) -l$(PRINTF)

server_bonus: server_bonus.o $(LIB)
	$(CC) $(CFLAGS) -o server $< -L$(LIBDIR) -l$(PRINTF)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) client server
	make -C $(LIBDIR) fclean

re: fclean all
