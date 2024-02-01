CC := cc
CFLAGS := -xc -g -O0 -std=c99 -Wall -Wextra -Wpedantic
INC := -I$(ADLMIDI_INCLUDE)
LIBS := -L$(ADLMIDI_LIBPATH) -lraylib -lADLMIDI
SRCS := audio.c dda.c ent.c main.c monsters.c player.c psprite.c res_man.c tile_map.c util.c world.c xform.c

all:
	@echo -----------------------------------------------------------------------------------
	@echo If you encounter errors, please pass ADLMIDI_INCLUDE and ADLMIDI_LIBPATH variables.
	@echo -----------------------------------------------------------------------------------
	$(CC) $(CFLAGS) $(SRCS)  -o wolf3d $(INC) $(LIBS)

adlmidi_test:
	$(CC) $(CFLAGS) audio.c adlmidi_test.c -o adlmidi_test $(INC) $(LIBS)
