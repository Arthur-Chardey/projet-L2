CC = gcc
CFLAGS   = -W -Wall -ansi -std=c99 -g
LIBS     = -L./SDL2_ttf/.libs -L./SDL2_image/.libs
LDFLAGS =  -lSDL2_ttf -lSDL2_image
LFLAGS   = 
INCLUDES = -I./SDL2_ttf -I./SDL2_image
EXEC = main
SRC = main.cpp
OBJ = $(SRCS:.c=.o)

all: $(EXEC)
main : $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf *.o *~	

mrproper: clean
	rm -rf $(EXEC)
