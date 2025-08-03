CC = gcc
ASM = nasm
CFLAGS = -Wall -O2 $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)
BUILD = build

all: $(BUILD)/game

$(BUILD)/game: $(BUILD)/logic.o $(BUILD)/graphics.o
	$(CC) $(BUILD)/logic.o $(BUILD)/graphics.o -o $(BUILD)/game $(LDFLAGS)

$(BUILD)/logic.o: logic.asm | $(BUILD)
	$(ASM) -f elf64 logic.asm -o $(BUILD)/logic.o

$(BUILD)/graphics.o: graphics.c | $(BUILD)
	$(CC) -c graphics.c -o $(BUILD)/graphics.o $(CFLAGS)

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

run:
	$(BUILD)/game