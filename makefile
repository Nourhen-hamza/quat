CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -g -fsanitize=leak -fsanitize=undefined  -fsanitize=address  
LDFLAGS=-lm -lSDL2

FOLDER = .
SOURCES = $(wildcard $(FOLDER)/*.c)
OBJECTS = $(SOURCES:.c=.o)

TARGET = quat

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)



.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJECTS)