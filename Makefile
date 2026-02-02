CC = gcc

CFLAGS = -std=c99 -Wall -Wextra
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm -lm

SRC = main.c map.c player.c renderer.c
OUT = raycaster.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: $(OUT)
	$(OUT)

clean:
	del /Q $(OUT) *.o map.bin 2>nul