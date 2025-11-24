CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O3
LDFLAGS = -L./raylib/lib -rpath @loader_path/raylib/lib
LIBS = -lraylib
FRAMEWORKS = -framework OpenGL -framework IOKit -framework Cocoa -framework CoreVideo -framework CoreAudio

INCLUDES = -I./raylib/include

TARGET = fractal
SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LIBS) $(FRAMEWORKS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

